#!/usr/bin/env python3
"""Compare original/native state sequences and real callers, without board I/O.

Only UART transmission and display refresh are intercepted. This is finite
functional evidence; instruction timing and interrupt interleavings are not modeled.
"""
import hashlib
import json
from pathlib import Path
import random
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE, UC_HOOK_MEM_WRITE
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
    UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
    UC_ARM_REG_R12, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
    UC_ARM_REG_XPSR,
)

if not __debug__:
    raise RuntimeError('Run verification without Python optimization (-O)')

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'recovery/tools'))
sys.path.insert(0, str(ROOT / 'firmware/tools'))
from parse_hex import parse_hex
from prepare_legacy import HEX_SHA

FLASH, RAM, STOP = 0x08000000, 0x20000000, 0x10000000
SP = RAM + 0x1680  # Original application initial MSP, not extra simulated SRAM.
PAYLOAD = RAM + 0x1200
REGS = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
        UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
        UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
        UC_ARM_REG_R12]
RANGES = {0x0800c85c: (0x0800c85c, 0x0800ca2c),
          0x08009e14: (0x08009e14, 0x08009e2c),
          0x0800c7c4: (0x0800c7c4, 0x0800c810),
          0x08009d84: (0x08009d84, 0x08009e04),
          0x0800964e: (0x0800964e, 0x08009694)}


class Machine:
    def __init__(self, image):
        self.u = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        self.u.mem_map(FLASH, 65536)
        self.u.mem_write(FLASH, image)
        # Cortex-M can map Flash or SRAM at zero. A native machine address of
        # zero is not automatically an invalid C-style buffer pointer.
        self.u.mem_map(0, 4096)
        self.u.mem_map(RAM, 8192)
        self.u.mem_map(STOP, 4096)
        self.u.hook_add(UC_HOOK_CODE, self.code)
        self.u.hook_add(UC_HOOK_MEM_WRITE, self.write)
        self.covered = set()

    def code(self, u, address, size, _):
        self.covered.add(address)
        self.minimum_sp = min(self.minimum_sp, u.reg_read(UC_ARM_REG_SP))
        self.extension_hit |= FLASH + 0xd000 <= address < FLASH + 0xf800
        if address == STOP:
            self.done = True
            u.emu_stop()
        elif address == 0x0800947c:
            pointer, length = u.reg_read(UC_ARM_REG_R0), u.reg_read(UC_ARM_REG_R1)
            self.events.append(('tx', pointer, length, bytes(u.mem_read(pointer, length))))
            u.reg_write(UC_ARM_REG_R0, 0)
            u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))
        elif address == 0x0800a65c:
            self.events.append(('refresh',))
            u.reg_write(UC_ARM_REG_R0, 0)
            u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))

    def write(self, _u, _access, address, size, value, _):
        assert RAM <= address and address + size <= RAM + 8192, ('unexpected write', hex(address), size)
        if RAM <= address < SP - 0x100:
            self.writes.append((address, size, value))

    def run(self, entry, args, register_seed):
        u = self.u
        u.reg_write(UC_ARM_REG_XPSR, 0x01000000 | (register_seed[0] & 0xf0000000))
        for i, reg in enumerate(REGS):
            u.reg_write(reg, register_seed[i])
        for reg, arg in zip(REGS[:4], args[:4]):
            u.reg_write(reg, arg)
        u.mem_write(SP, (args[4] if len(args) > 4 else 0).to_bytes(4, 'little'))
        u.reg_write(UC_ARM_REG_SP, SP)
        u.reg_write(UC_ARM_REG_LR, STOP | 1)
        self.events, self.writes, self.done = [], [], False
        self.minimum_sp, self.extension_hit = SP, False
        u.emu_start(entry | 1, 0, count=300000)
        assert self.done and u.reg_read(UC_ARM_REG_SP) == SP, ('return/SP', hex(entry))
        for i in range(4, 12):
            assert u.reg_read(REGS[i]) == register_seed[i], ('callee-saved', hex(entry), i)
        return bytes(u.mem_read(RAM, 8192)), self.events


def main():
    paths = sorted(set((ROOT / 'firmware/src').rglob('*.c')) |
                   set((ROOT / 'firmware/include').rglob('*.h')) |
                   {p for p in (ROOT / 'firmware/platform').rglob('*') if p.is_file()} |
                   set((ROOT / 'firmware/tools').glob('*.py')) |
                   {Path(__file__).resolve(), ROOT / 'Makefile', ROOT / 'firmware/Makefile',
                    ROOT / 'stm32_fw.hex', ROOT / 'firmware/build/charge.bin',
                    ROOT / 'recovery/tools/parse_hex.py',
                    ROOT / 'recovery/full_assembly/instructions.json'})
    hashes = {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths}
    raw, memory, *_ = parse_hex(ROOT / 'stm32_fw.hex')
    assert hashlib.sha256(raw).hexdigest() == HEX_SHA
    original = bytes(memory[a] for a in range(FLASH, FLASH + 65536))
    native = (ROOT / 'firmware/build/charge.bin').read_bytes()
    assert len(native) == 65536
    old, new = Machine(original), Machine(native)
    rng = random.Random(0x51e9)
    counts, depth = {}, {}
    expected_hits = 0
    live_floor = SP

    def reset():
        nonlocal live_floor
        live_floor = SP
        state = rng.randbytes(8192)
        for machine in (old, new):
            machine.u.mem_write(RAM, state)
            machine.u.mem_write(0, state[:4096])

    def write(address, data):
        for machine in (old, new):
            machine.u.mem_write(address, data)

    def compare(kind, entry, args=(), extension=True, ordered_writes=False):
        nonlocal expected_hits, live_floor
        registers = [rng.getrandbits(32) for _ in REGS]
        left, right = old.run(entry, args, registers), new.run(entry, args, registers)
        floor = min(old.minimum_sp, new.minimum_sp)
        assert floor >= SP - 0x100, ('unexpected stack growth', kind, hex(floor))
        # A returned frame remains dead after later, shallower calls. Exclude
        # the union of transient frames across this sequence, not just this call.
        # No blanket exclusion of upper SRAM is used.
        live_floor = min(live_floor, floor)
        n = live_floor - RAM
        assert left[0][:n] == right[0][:n], (
            'live RAM below stack', kind, counts.get(kind, 0), args,
            [hex(RAM+i) for i, (a, b) in enumerate(zip(left[0][:n], right[0][:n])) if a != b][:16])
        assert left[0][SP-RAM:] == right[0][SP-RAM:], ('caller-owned upper RAM', kind, args)
        assert left[1] == right[1], ('I/O trace', kind, args, left[1], right[1])
        assert new.extension_hit == extension, ('unexpected extension execution', kind, args)
        if extension:
            assert new.extension_hit, ('did not execute C', kind, args)
            expected_hits += 1
        if ordered_writes:
            assert old.writes == new.writes, ('ordered shared-state writes', kind, args)
        counts[kind] = counts.get(kind, 0) + 1
        previous = depth.setdefault(hex(entry), {'original': 0, 'native': 0})
        previous['original'] = max(previous['original'], SP - old.minimum_sp)
        previous['native'] = max(previous['native'], SP - new.minimum_sp)

    # Exercise every possible existing packed byte, preserving other channels.
    for channel in range(12):
        for packed in range(256):
            for enabled in (0, 1):
                reset()
                write(RAM + 0xdd + channel // 4, bytes([packed]))
                compare('packed_state', 0x0800c85c, (channel, enabled), ordered_writes=True)
    for channel in range(12, 256):
        reset()
        compare('invalid_channel', 0x0800c85c, (channel, 1), ordered_writes=True)
    # Native callers supply registers, not C conversions. The original entry
    # reduces channel modulo 256, but tests all 32 bits of the enable value.
    # r0=256/r1=1 is a regression for the former narrow bridge signature.
    for high in (0, 0x100, 0x10000, 0xffffff00):
        for channel in range(256):
            for enabled in (0, 1, 0x100, 0x80000000, 0xffffffff):
                reset()
                compare('raw_channel_registers', 0x0800c85c,
                        (high | channel, enabled), ordered_writes=True)
    # Multiplication by the 52-byte record stride wraps at 32 bits; these raw
    # inputs deliberately alias the same twelve valid records in the original.
    for high in (0, 0x40000000, 0x80000000, 0xc0000000):
        for channel in range(12):
            reset()
            compare('raw_clear_registers', 0x08009e14, (high | channel,), ordered_writes=True)

    # Independent state persists between calls; repeated operations must agree.
    for _ in range(24):
        reset()
        for _ in range(64):
            channel = rng.randrange(12)
            if rng.randrange(4):
                compare('channel_sequence', 0x0800c85c,
                        (channel, rng.choice((0, 1, 2, 255))), ordered_writes=True)
            else:
                compare('clear_sequence', 0x08009e14, (channel,), ordered_writes=True)

    # Original upstream reset caller: all 2^12 active/inactive channel masks.
    for mask in range(4096):
        reset()
        for channel in range(12):
            write(RAM + 0x5e4 + channel * 52,
                  ((rng.getrandbits(32) or 1) if mask & (1 << channel) else 0).to_bytes(4, 'little'))
        write(RAM + 0x876, (mask % 3).to_bytes(2, 'little'))
        compare('reset_caller', 0x08009d84, ordered_writes=True)

    # Send valid/rejected lengths with multiple payload contents and all byte
    # command/subcommand/prefix values. Payload never aliases the TX buffer.
    reset()
    for length in range(256):
        for pattern in range(4):
            data = (bytes(length) if pattern == 0 else bytes([255]) * length
                    if pattern == 1 else bytes(range(length)) if pattern == 2
                    else rng.randbytes(length))
            write(PAYLOAD, data or b'\0')
            compare('tx_lengths', 0x0800c7c4,
                    (length, length, 255-length, PAYLOAD, length ^ 0xaa), extension=True)
    for byte in range(256):
        for length in (0, 1, 2, 127, 165, 166):
            write(PAYLOAD, rng.randbytes(max(length, 1)))
            compare('tx_fields', 0x0800c7c4, (byte, length, byte ^ 0xff, PAYLOAD, byte))
    for value in (0x100, 0x101, 0x10001, 0x80000000, 0xffffffff):
        for length in (0, 1, 166, 167, 256, 0x10000, 0xffffffff):
            reset()
            compare('tx_raw_registers', 0x0800c7c4,
                    (value, length, value ^ 0xff, PAYLOAD, value))
    # The old native entry reads address zero when a nonempty payload points
    # there. Model both documented low-memory mappings, without claiming to
    # emulate the board's remap peripheral or synchronization.
    for alias in ('sram', 'flash'):
        for length in range(167):
            reset()
            if alias == 'flash':
                for machine in (old, new):
                    machine.u.mem_write(0, original[:4096])
            compare('tx_zero_address', 0x0800c7c4, (0x55, length, 1, 0, 0xaa))

    # Execute the unchanged real identifier caller, including its stack payload.
    for mode in range(256):
        reset()
        write(PAYLOAD, rng.randbytes(4))
        write(PAYLOAD + 8, bytes([mode, rng.randrange(256), rng.randrange(256)]))
        compare('identifier_caller', 0x0800964e, (PAYLOAD, PAYLOAD + 8),
                extension=mode in (0x55, 0x66))
    for pointers in ((0, PAYLOAD + 8), (PAYLOAD, 0), (0, 0)):
        reset()
        compare('identifier_null', 0x0800964e, pointers, extension=False)

    inventory = json.loads((ROOT / 'recovery/full_assembly/instructions.json').read_text())
    addresses = {int(item['address'], 16) for item in inventory}
    coverage = {}
    for entry, (lo, hi) in RANGES.items():
        expected = {address for address in addresses if lo <= address < hi}
        visited = expected & old.covered
        coverage[hex(entry)] = {'instructions': len(expected), 'executed': len(visited),
                                'unexecuted': [hex(a) for a in sorted(expected - visited)]}
    assert all(hashlib.sha256(p.read_bytes()).hexdigest() == hashes[str(p.relative_to(ROOT))]
               for p in paths), 'Inputs changed during run'

    report = {
        'result': 'PASS', 'cases': counts, 'total_cases': sum(counts.values()),
        'calls_required_to_execute_C': expected_hits, 'observed_stack_bytes': depth,
        'original_hex_sha256': HEX_SHA,
        'native_bin_sha256': hashlib.sha256(native).hexdigest(),
        'test_sha256': hashlib.sha256(Path(__file__).read_bytes()).hexdigest(),
        'input_sha256': hashes,
        'original_instruction_coverage': coverage,
        'limitations': ['Finite synchronous scenarios; no full-system equivalence proof.',
                        'UART and display-refresh calls intercepted, not executed on hardware.',
                        'Observed stack depths are selected-call measurements, not whole-system bounds.',
                        'No IRQ/DMA interleavings, physical timing, or dynamic caller completeness proof.'],
    }
    output = ROOT / 'firmware/build/native_sequences_verification.json'
    output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k != 'input_sha256'}, indent=2))


if __name__ == '__main__':
    main()
