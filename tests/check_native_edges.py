#!/usr/bin/env python3
"""Native storage/config edge differentials against immutable original Thumb.

Run after `make native`. I2C, tick, and physical pulse-output boundaries are
scripted except for actual I2C NULL/zero-size and busy/locked early exits.
The original/native implementations and selected callers execute.
No board access, compilation, or mutation of original firmware is performed.
"""
import hashlib
import json
from pathlib import Path
import random
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
    UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
    UC_ARM_REG_R12, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
    UC_ARM_REG_XPSR,
)

if not __debug__:
    raise RuntimeError('Run without Python optimization (-O)')
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'recovery/tools'))
from parse_hex import parse_hex
from reporting import report_path

HEX_SHA = '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'
FLASH, RAM, STOP = 0x08000000, 0x20000000, 0x10000000
SP, DATA, CONFIG = RAM + 0x1f00, RAM + 0x1000, RAM + 0x854
READ, WAIT, WRITE, APPLY = 0x08007498, 0x080074c4, 0x080074fc, 0x0800bcd8
READ_WORD, WRITE_WORD, APPLY_CALLER = 0x0800a46c, 0x0800a47c, 0x0800c830
READ_IO, WRITE_IO, PROBE_IO, TICK, PULSE = (
    0x08005fb8, 0x0800610c, 0x08005ea8, 0x08005d54, 0x0800cdb8)
REGS = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
        UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
        UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
        UC_ARM_REG_R12]
RANGES = {READ: (READ, 0x080074c0), WAIT: (WAIT, 0x080074f6),
          WRITE: (WRITE, 0x080075d4), APPLY: (APPLY, 0x0800be1c)}


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


class Machine:
    def __init__(self, image):
        self.u = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        self.u.mem_map(FLASH, 65536)
        self.u.mem_write(FLASH, image)
        self.u.mem_map(RAM, 8192)
        self.u.mem_map(STOP, 4096)
        self.u.hook_add(UC_HOOK_CODE, self.hook)
        self.covered = set()

    def hook(self, u, address, size, user):
        stack = u.reg_read(UC_ARM_REG_SP)
        assert RAM <= stack <= SP, ('stack outside mapped entry bounds', hex(address), hex(stack))
        self.minimum_sp = min(self.minimum_sp, stack)
        if any(lo <= address < hi for lo, hi in RANGES.values()):
            self.covered.add(address)
        self.extension_hit |= 0x0800d000 <= address < 0x0800f800
        if address == STOP:
            self.stopped = True
            u.emu_stop()
            return
        if address not in (READ_IO, WRITE_IO, PROBE_IO, TICK, PULSE):
            return
        r = [u.reg_read(reg) for reg in REGS[:4]]
        stack = u.reg_read(UC_ARM_REG_SP)
        word = lambda p: int.from_bytes(u.mem_read(p, 4), 'little')
        if address in (READ_IO, WRITE_IO):
            pointer, count, timeout = [word(stack + 4*i) for i in range(3)]
            assert r[0] == RAM + 0xb6c and r[1] == 0xa0 and r[3] == 2
            assert timeout == (1000 if address == READ_IO else 500)
            if self.options.get('real_driver'):
                self.events.append(('real_read' if address == READ_IO else 'real_write',
                                    *r, pointer, count, timeout))
                # NULL/zero-size and busy/locked prefixes return before MMIO;
                # run those actual instructions, including handle error writes.
                return
            if address == READ_IO:
                result = self.options.get('read_status', 0)
                # Partial reads are possible even on failure; compare resulting
                # live buffer effects rather than assuming error means no writes.
                written = count if result == 0 else min(count, self.options.get('partial_read', 0))
                payload = bytes((r[2] + i*7 + 0x53) & 255 for i in range(written))
                if payload:
                    u.mem_write(pointer, payload)
                self.events.append(('read', *r, pointer, count, timeout, payload.hex(), result))
            else:
                self.writes += 1
                result = (self.options.get('write_status', 7)
                          if self.writes == self.options.get('fail_write', 0) else 0)
                if self.options.get('capture_payload', True):
                    payload = bytes(u.mem_read(pointer, count)).hex() if count else ''
                else:
                    payload = '<not-read-by-script>'
                self.events.append(('write', *r, pointer, count, timeout, payload, result))
                self.wait_ticks = self.wait_probes = 0
        elif address == PROBE_IO:
            timeout = word(stack)
            assert r == [RAM + 0xb6c, 0xa0, 0, 0] and timeout == 50
            self.wait_probes += 1
            timeout_page = self.options.get('timeout_page')
            busy = self.options.get('busy', 0)
            if timeout_page is not None:
                busy = None if self.writes == timeout_page else 0
            result = (self.options.get('probe_status', 3)
                      if busy is None or self.wait_probes <= busy else 0)
            self.events.append(('probe', *r, timeout, result))
        elif address == TICK:
            offsets = self.options.get('tick_offsets', (0, 1, 2, 501))
            assert self.wait_ticks < len(offsets), 'Scripted ticks exhausted'
            result = (self.options.get('tick_start', 0) +
                      max(0, self.writes - 1)*1000 + offsets[self.wait_ticks]) & 0xffffffff
            self.wait_ticks += 1
            self.events.append(('tick', result))
        else:
            assert r[0] == 0x26
            self.events.append(('pulse', r[0]))
            result = 0
        u.reg_write(UC_ARM_REG_R0, result)
        u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))

    def run(self, entry, args, initial, options):
        u = self.u
        u.mem_write(RAM, initial)
        self.events, self.stopped, self.extension_hit = [], False, False
        self.minimum_sp = SP
        self.writes = self.wait_ticks = self.wait_probes = 0
        self.options = options
        u.reg_write(UC_ARM_REG_XPSR, 0x01000000)
        for i, reg in enumerate(REGS):
            u.reg_write(reg, 0x13570000 + i)
        for reg, value in zip(REGS, args):
            u.reg_write(reg, value)
        u.reg_write(UC_ARM_REG_SP, SP)
        u.reg_write(UC_ARM_REG_LR, STOP | 1)
        u.emu_start(entry | 1, 0, count=200000)
        assert self.stopped, ('instruction budget exhausted', hex(entry), args, options)
        assert u.reg_read(UC_ARM_REG_SP) == SP
        for i in range(4, 12):
            assert u.reg_read(REGS[i]) == 0x13570000 + i, ('callee-saved register', i)
        return (bytes(u.mem_read(RAM, 8192)), self.events,
                [u.reg_read(reg) for reg in REGS], self.minimum_sp)


def main():
    paths = sorted(set((ROOT/'firmware/src').rglob('*.c')) |
                   set((ROOT/'firmware/include').rglob('*.h')) |
                   set((ROOT/'firmware/platform').rglob('*.c')) |
                   set((ROOT/'firmware/platform').rglob('*.S')) |
                   set((ROOT/'firmware/platform').rglob('*.ld')) |
                   set((ROOT/'firmware/tools').glob('*.py')) |
                   {Path(__file__).resolve(), ROOT/'firmware/Makefile',
                    ROOT/'recovery/tools/parse_hex.py',
                    ROOT/'recovery/full_assembly/instructions.json',
                    ROOT/'firmware/build/charge.bin', ROOT/'firmware/build/charge.hex',
                    ROOT/'stm32_fw.hex'})
    hashes = {str(p.relative_to(ROOT)): digest(p) for p in paths}
    raw, memory, *_ = parse_hex(ROOT/'stm32_fw.hex')
    assert hashlib.sha256(raw).hexdigest() == HEX_SHA
    original = bytes(memory[a] for a in range(FLASH, FLASH + 65536))
    native = (ROOT/'firmware/build/charge.bin').read_bytes()
    assert len(native) == 65536 and native != original
    _, hex_memory, *_ = parse_hex(ROOT/'firmware/build/charge.hex')
    assert hex_memory == {FLASH + i: b for i, b in enumerate(native)}
    old, new = Machine(original), Machine(native)
    rng = random.Random(0x7450bcd8)
    counts = {}
    stack_usage = {}

    def compare(group, entry, args, options=None, initial=None, expected=None, extension=True):
        initial = initial if initial is not None else rng.randbytes(8192)
        options = options or {}
        a = old.run(entry, args, initial, options)
        b = new.run(entry, args, initial, options)
        context = (group, hex(entry), args, options)
        floor = min(a[3], b[3])
        # Each case starts from identical complete SRAM. Exclude only the union
        # of private stack frames actually observed during this pair of runs.
        # The 512-byte external input/output allocation must remain live. The
        # real word wrappers' local buffers are checked through I/O and returns.
        assert DATA + 512 <= floor, (context, 'stack overlaps external data buffer')
        assert a[0][:floor-RAM] == b[0][:floor-RAM], (context, 'RAM below stack differs')
        assert a[0][SP-RAM:] == b[0][SP-RAM:], (context, 'caller RAM at/above entry SP differs')
        assert a[1] == b[1], (context, 'I/O differs', a[1], b[1])
        usage = stack_usage.setdefault(f'0x{entry:08x}', {'original_bytes': 0, 'native_bytes': 0})
        usage['original_bytes'] = max(usage['original_bytes'], SP-a[3])
        usage['native_bytes'] = max(usage['native_bytes'], SP-b[3])
        assert new.extension_hit == extension, (context, 'unexpected extension execution')
        if entry in (READ, WAIT, WRITE, READ_WORD, WRITE_WORD):
            assert a[2][0] == b[2][0], (context, 'return differs')
            if expected is not None:
                assert b[2][0] == expected, (context, 'unexpected return', b[2][0], expected)
        for i in {READ: (1, 2, 12), WAIT: (12,)}.get(entry, ()):
            assert a[2][i] == b[2][i], (context, 'legacy preserved register', i)
        counts[group] = counts.get(group, 0) + 1
        return b

    # Exhaust every within-page alignment and both sides of the first/full/tail
    # page boundaries, while all nonzero buffers remain inside real 8 KiB RAM.
    for offset in range(128):
        first = 128 - offset
        lengths = sorted({0, 1, max(0, first-1), first, first+1,
                          first+127, first+128, first+129, 511})
        for length in lengths:
            for entry in (READ, WRITE):
                compare('page_boundaries', entry, (0x1200+offset, DATA, length), expected=0)
        for length in sorted({0, 1, first-1, first, first+1, 65535}):
            for entry in (READ, WRITE):
                compare('address_limit', entry, (0xff80+offset, DATA, length),
                        expected=int(length > first))

    for entry in (READ, WRITE):
        for address in (0, 1, 127, 128, 65535):
            compare('zero_length_null', entry, (address, 0, 0), expected=0)
        for address, length in ((1, 65535), (0, 65535)):
            # Full legal uint16 ranges, failing on the first port call; no
            # synthetic 64 KiB SRAM allocation is used for this boundary.
            compare('maximum_valid_range', entry, (address, DATA, length),
                    {'read_status': 7, 'fail_write': 1}, expected=7 if entry == READ else 1)

    # Raw machine entries receive full registers, even though portable APIs
    # intentionally require uint16 arguments. Bound unusual writes by forcing
    # failure on call 1/2; compare raw arguments without dereferencing arbitrary
    # pointers/lengths in the scripted device callback.
    raw_addresses = (0, 0xffff, 0x10000, 0x10001, 0x80000000, 0xffff0000, 0xffffff80, 0xffffffff)
    raw_sizes = (0, 1, 127, 128, 129, 65535, 65536, 65664, 0x80000000, 0x80000080, 0xffffffff)
    for address in raw_addresses:
        for size in raw_sizes:
            rejected = ((0x10000-address) & 0xffffffff) < size
            compare('raw_register_read', READ, (address, DATA, size),
                    {'read_status': 7}, expected=1 if rejected else 7)
            for failure in (1, 2):
                compare('raw_register_write', WRITE, (address, DATA, size),
                        {'fail_write': failure, 'capture_payload': False},
                        expected=1 if rejected or failure == 1 else None)
    # The previous native bridge truncated 65664 to 128 and returned success.
    regression = compare('raw_write_regression', WRITE, (0xffff0000, DATA, 65664),
                         {'fail_write': 2}, expected=1)
    writes = [event for event in regression[1] if event[0] == 'write']
    assert [(e[3], e[6]) for e in writes] == [(0xffff0000, 128), (0x80, 128)]

    for entry in (READ, WRITE):
        for state, locked in ((0x20, 0), (0, 0), (0x21, 0), (0x20, 1)):
            for pointer, size in ((0, 1), (0, 128), (0, 0), (DATA, 0), (DATA, 1)):
                # Ready, unlocked, nonempty buffers would reach real MMIO.
                if state == 0x20 and locked == 0 and pointer and size:
                    continue
                initial = bytearray(rng.randbytes(8192))
                initial[0xbac] = locked
                initial[0xbad] = state
                bad_buffer = pointer == 0 or size == 0
                driver_return = 2 if state != 0x20 or (locked and not bad_buffer) else 1
                result = compare('real_driver_validation', entry, (0, pointer, size),
                                 {'real_driver': True}, initial=bytes(initial),
                                 expected=driver_return if entry == READ else 1)
                if state == 0x20 and bad_buffer:
                    assert int.from_bytes(result[0][0xbb0:0xbb4], 'little') == 0x200

    for status in (1, 2, 3, 7, 0x80000000, 0xffffffff):
        for partial in (0, 1, 17):
            compare('read_errors', READ, (127, DATA, 17),
                    {'read_status': status, 'partial_read': partial}, expected=status)
        # offset 127 + 258 bytes = 1 + 128 + 128 + 1, covering
        # failure on the initial fragment, full pages, and final fragment.
        for failure in range(1, 5):
            compare('write_errors', WRITE, (127, DATA, 258),
                    {'fail_write': failure, 'write_status': status}, expected=1)

    for start in (0, 0xffffff00, 0xffffffff):
        for delta in (499, 500, 501):
            for status in (1, 3, 0xffffffff):
                options = {'busy': 1, 'probe_status': status,
                           'tick_start': start, 'tick_offsets': (0, delta)}
                for entry, args in ((WAIT, ()), (WRITE, (127, DATA, 258))):
                    compare('timeout_threshold', entry, args, options, expected=int(delta > 500))
        for page in range(1, 5):
            compare('timeout_each_page', WRITE, (127, DATA, 258),
                    {'timeout_page': page, 'tick_start': start,
                     'tick_offsets': (0, 499, 500, 501)}, expected=1)
        for busy in (0, 1, 2, 3):
            compare('retry_sequence', WAIT, (),
                    {'busy': busy, 'tick_start': start, 'tick_offsets': (0, 499, 500, 501)},
                    expected=int(busy == 3))

    # Real legacy wrappers use local stack buffers and consume read data even
    # when the port returns an error; compare return values and emitted bytes.
    for address in (0, 127, 128, 65534, 65535):
        for options in ({}, {'read_status': 7}, {'read_status': 2, 'partial_read': 1},
                        {'fail_write': 1}, {'timeout_page': 1}):
            compare('storage_callers', READ_WORD, (address,), options)
            compare('storage_callers', WRITE_WORD, (address, 0x1234abcd), options)

    def config_case(group, endian, limit, payload, caller=False, pending=0, null=False):
        initial = bytearray(rng.randbytes(8192))
        initial[0x854+42:0x854+44] = limit.to_bytes(2, 'little')
        initial[DATA-RAM:DATA-RAM+23] = payload
        initial[0x12a:0x12c] = pending.to_bytes(2, 'little')
        entry, args = (APPLY_CALLER, (DATA,)) if caller else (APPLY, (0 if null else DATA, endian))
        compare(group, entry, args, initial=bytes(initial), extension=not (caller and pending))

    for endian in range(256):
        config_case('all_endian_selectors', endian, 0x1234, bytes(range(23)))
    for endian in (0x100, 0x101, 0x10001, 0x80000001, 0xffffffff):
        config_case('raw_endian_selectors', endian, 0x1234, bytes(range(23)))
    for endian in (0, 1, 2, 255):
        order = 'big' if endian == 1 else 'little'
        for limit in (0, 1, 239, 240, 250, 2500, 65534, 65535):
            values = sorted({0, 1, max(0, limit-1), limit, min(65535, limit+1), 65535})
            for first in values:
                for second in values:
                    payload = bytearray(rng.randbytes(23))
                    payload[:2] = first.to_bytes(2, order)
                    payload[2:4] = second.to_bytes(2, order)
                    config_case('config_limit', endian, limit, payload)
        for byte in (0, 1, 249, 250, 251, 254, 255):
            for value in (0, 1, 2499, 2500, 2501, 65535):
                payload = bytearray(rng.randbytes(23))
                payload[6] = byte
                payload[21] = byte
                for pos in (7, 9, 11, 13):
                    payload[pos:pos+2] = value.to_bytes(2, order)
                config_case('config_clamps', endian, 65535, payload)
        config_case('config_null', endian, 250, bytes(23), null=True)
    for _ in range(256):
        config_case('config_random', rng.randrange(256), rng.randrange(65536), rng.randbytes(23))
    for pending in (0, 1, 800, 1600, 65535):
        for _ in range(8):
            config_case('config_caller', 0, rng.randrange(65536), rng.randbytes(23), True, pending)

    inventory = json.loads((ROOT/'recovery/full_assembly/instructions.json').read_text())
    # Inventory is a list of instruction records, not a new disassembly pass.
    instructions = {int(item['address'], 16) for item in inventory}
    coverage = {}
    for entry, (lo, hi) in RANGES.items():
        expected = {a for a in instructions if lo <= a < hi}
        visited = old.covered & expected
        coverage[f'0x{entry:08x}'] = {'instructions': len(expected), 'executed': len(visited),
                                     'unexecuted': [f'0x{a:08x}' for a in sorted(expected-visited)]}
    assert all(digest(p) == hashes[str(p.relative_to(ROOT))] for p in paths), 'Inputs changed during run'
    result = {'result': 'PASS', 'cases': counts, 'total_cases': sum(counts.values()),
              'original_hex_sha256': HEX_SHA, 'native_bin_sha256': hashlib.sha256(native).hexdigest(),
              'original_instruction_coverage': coverage,
              'observed_maximum_stack_bytes_by_entry': stack_usage,
              'checks': ['original Thumb versus linked native ARM instructions',
                         '8 KiB SRAM; globals, data guards, restored SP and callee-saved registers',
                         'ordered I2C arguments, status, partial read effects, tick values and pulses',
                         'all 128 page offsets and all 256 endian selector values',
                         '499/500/501 timeout boundaries including uint32 wrap',
                         'full-register storage range/page-count and endian regressions',
                         'actual I2C driver NULL/zero-size/busy/locked return and handle effects',
                         'real legacy read/write-word and config-throttle callers'],
              'limitations': ['Most device behavior is scripted; no physical hardware, IRQ/DMA or timing validation.',
                              'Only the observed union of private stack frames is excluded from RAM comparison.',
                              'Stack depths include executed driver prefixes but exclude intercepted driver bodies and IRQ frames; not a whole-firmware bound.',
                              'Exceptional full-register writes are bounded by scripted early failures; not every 32-bit combination is covered.',
                              'Actual driver execution covers only NULL/zero-size and busy/locked early exits, before MMIO.',
                              'Overlapping config/payload remains outside the portable API contract.',
                              'Maximum valid transfers tested with immediate I/O failure; no full 64 KiB data buffer.',
                              'Finite samples and instruction coverage do not prove all state/branch combinations.'],
              'input_sha256': hashes}
    target = report_path('firmware/native_edges_verification.json')
    target.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({k: v for k, v in result.items() if k != 'input_sha256'}, indent=2))


if __name__ == '__main__':
    main()
