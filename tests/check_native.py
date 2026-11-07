#!/usr/bin/env python3
"""Compare the linked ARM migration image with the immutable original HEX.

Execute actual C machine code through original entry addresses; device calls
are intercepted, never replaced in the delivered binary. Real 8 KiB SRAM.
"""
import hashlib
import json
from pathlib import Path
import random
import sys

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import *

if not __debug__:
    raise RuntimeError("Run verification without Python optimization (-O)")

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'recovery/tools'))
sys.path.insert(0, str(ROOT / 'firmware/tools'))
from parse_hex import parse_hex
from prepare_legacy import ENTRIES, HEX_SHA
EXPECTED_ENTRIES = {0x08007498, 0x080074c4, 0x080074fc, 0x08009e14,
                    0x0800bcd8, 0x0800c7c4, 0x0800c85c}
assert set(ENTRIES) == EXPECTED_ENTRIES, 'A required native migration was removed'
raw, memory, *_ = parse_hex(ROOT / 'stm32_fw.hex')
assert hashlib.sha256(raw).hexdigest() == HEX_SHA
original = bytes(memory[a] for a in range(0x08000000, 0x08010000))
updated = (ROOT / 'firmware/build/charge.bin').read_bytes()
assert len(updated) == len(original) == 65536
_, hex_memory, *_ = parse_hex(ROOT / 'firmware/build/charge.hex')
assert hex_memory == {0x08000000 + i: value for i, value in enumerate(updated)}
allowed = {a - 0x08000000 + i for a in ENTRIES for i in range(16)} | set(range(0xd000, 0xf800))
changed = {i for i, (a, b) in enumerate(zip(original, updated)) if a != b}
assert changed and changed <= allowed, 'Unexpected change outside entry veneers / C extension'
assert original[:0x4000] == updated[:0x4000]
assert original[0xf800:] == updated[0xf800:]
assert original[0xd000:0xf800] == b'\xff' * 0x2800

RAM = 0x20000000
SP = RAM + 0x1f00
DATA = RAM + 0x1200
STOP = 0x10000000  # Separate mapped sentinel, never inside new C extension.
REGS = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
        UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
        UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11, UC_ARM_REG_R12]
rng = random.Random(0xc0de)
cases = 0

class Machine:
    def __init__(self, binary):
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
        self.uc.mem_map(0x08000000, 65536)
        self.uc.mem_write(0x08000000, binary)
        self.uc.mem_map(RAM, 8192)
        self.uc.mem_map(STOP, 4096)
        self.uc.hook_add(UC_HOOK_CODE, self.hook)

    def hook(self, u, address, size, user):
        if 0x0800d000 <= address < 0x0800f800:
            self.extension_hit = True
        if address == STOP:
            self.stopped = True
            u.emu_stop()
            return
        if address not in (0x0800947c, 0x08005fb8, 0x0800610c, 0x08005ea8, 0x08005d54, 0x0800a65c):
            return
        r = [u.reg_read(reg) for reg in REGS[:4]]
        ret = 0
        if address == 0x0800947c:
            self.events.append(('tx', r[0], r[1], bytes(u.mem_read(r[0], r[1]))))
        elif address in (0x08005fb8, 0x0800610c):
            stack = u.reg_read(UC_ARM_REG_SP)
            p, n, timeout = [int.from_bytes(u.mem_read(stack + 4*i, 4), 'little') for i in range(3)]
            read = address == 0x08005fb8
            payload = bytes((i * 7) & 255 for i in range(n)) if read else bytes(u.mem_read(p, n)) if n else b''
            self.events.append(('read' if read else 'write', *r, p, n, timeout, payload))
            self.writes += 1
            ret = 3 if self.mode == 'io_fail' or (self.mode == 'second_write_fail' and self.writes == 2) else 0
            if read and not ret and n:
                u.mem_write(p, payload)
        elif address == 0x08005ea8:
            timeout = int.from_bytes(u.mem_read(u.reg_read(UC_ARM_REG_SP), 4), 'little')
            self.events.append(('probe', *r, timeout))
            assert r == [0x20000b6c, 0xa0, 0, 0] and timeout == 50
            self.probes += 1
            ret = 1 if self.mode == 'timeout' or (self.mode == 'retry' and self.probes <= 2) else 0
        elif address == 0x08005d54:
            ret = self.tick & 0xffffffff
            self.tick += 251
            self.events.append(('tick', ret))
        else:
            self.events.append(('refresh',))
        u.reg_write(UC_ARM_REG_R0, ret)
        u.reg_write(UC_ARM_REG_PC, u.reg_read(UC_ARM_REG_LR))

    def run(self, address, args, ram, mode):
        u = self.uc
        u.mem_write(RAM, ram)
        for i, reg in enumerate(REGS):
            u.reg_write(reg, 0x11110000 + i)
        for reg, value in zip(REGS, args[:4]):
            u.reg_write(reg, value)
        if len(args) > 4:
            u.mem_write(SP, args[4].to_bytes(4, 'little'))
        u.reg_write(UC_ARM_REG_SP, SP)
        u.reg_write(UC_ARM_REG_LR, STOP | 1)
        self.events, self.stopped = [], False
        self.extension_hit = False
        self.mode, self.probes, self.writes, self.tick = mode, 0, 0, 0xffffff00
        u.emu_start(address | 1, 0, count=200000)
        assert self.stopped, hex(address)
        assert u.reg_read(UC_ARM_REG_SP) == SP, ('SP', hex(address))
        for i in range(4, 12):
            assert u.reg_read(REGS[i]) == 0x11110000 + i, ('callee-saved', hex(address), i)
        return bytes(u.mem_read(RAM, 0x1800)), self.events, [u.reg_read(r) for r in REGS]

old, new = Machine(original), Machine(updated)

def compare(address, args=(), mode='ok', ram=None):
    global cases
    if ram is None:
        ram = rng.randbytes(8192)
    a, b = old.run(address, args, ram, mode), new.run(address, args, ram, mode)
    if address in EXPECTED_ENTRIES:
        assert new.extension_hit, (hex(address), 'Native entry did not execute new C extension')
    assert a[:2] == b[:2], (hex(address), args, mode, 'RAM or device trace mismatch')
    if address in (0x08007498, 0x080074c4, 0x080074fc):
        assert a[2][0] == b[2][0], (hex(address), 'return')
    preserve = {0x08007498: [1, 2, 12], 0x080074c4: [12],
                0x08009e14: [3, 12], 0x0800c85c: []}.get(address, [])
    for i in preserve:
        assert a[2][i] == b[2][i], (hex(address), 'original ABI', i)
    cases += 1

for channel in range(256):
    for enabled in (0, 1, 2, 255):
        compare(0x0800c85c, (channel, enabled))
for channel in range(12):
    compare(0x08009e14, (channel,))
for endian in range(3):
    for _ in range(80):
        compare(0x0800bcd8, (DATA, endian))
compare(0x0800bcd8, (0, 0))
for length in range(256):
    compare(0x0800c7c4, (rng.randrange(256), length, rng.randrange(256), DATA, rng.randrange(256)))
for address, size in ((0, 0), (0, 1), (127, 1), (127, 2), (128, 128),
                      (1, 511), (65535, 1), (65535, 2), (65500, 36), (65500, 37)):
    for mode in ('ok', 'io_fail', 'second_write_fail', 'timeout', 'retry'):
        compare(0x080074fc, (address, DATA, size), mode)
        compare(0x08007498, (address, DATA, size), mode)
for mode in ('ok', 'timeout', 'retry'):
    compare(0x080074c4, (), mode)
# Real caller exercises the nonstandard r3 contract after clear_channel and
# channel state updates. Both zero/nonzero countdown branches are covered.
for pattern in range(6):
    ram = bytearray(rng.randbytes(8192))
    for ch in range(12):
        value = 0 if (ch + pattern) % 3 else 100
        ram[0x5e4 + ch*52:0x5e8 + ch*52] = value.to_bytes(4, 'little')
    compare(0x08009d84, (), ram=bytes(ram))
result = {
    'result': 'PASS', 'native_differential_cases': cases,
    'changed_bytes': len(changed), 'original_hex_sha256': HEX_SHA,
    'native_bin_sha256': hashlib.sha256(updated).hexdigest(),
    'checks': ['64 KiB BIN/HEX agree', 'Boot/metadata/config unchanged',
               'only seven entry veneers and App extension changed',
               'Cortex-M0+ compiled C through real original entry points',
               '8 KiB SRAM, stack and callee-saved ABI', 'all seven entries execute the C extension',
               'clear r3, read r1/r2, selected shim r12 preservation',
               'whole channel-reset caller', 'ordered I2C/TX effects and errors'],
    'limitations': ['Peripheral calls intercepted for comparison; no physical board.',
                    'No IRQ/DMA interleaving, cycle timing, stack high-water proof or full main run.',
                    'Boot and most application logic deliberately remain legacy assembly.']
}
source_paths = sorted(set((ROOT / 'firmware/src').rglob('*.c')) |
                      set((ROOT / 'firmware/include').rglob('*.h')) |
                      set((ROOT / 'firmware/platform').rglob('*.c')) |
                      set((ROOT / 'firmware/platform').rglob('*.S')) |
                      set((ROOT / 'firmware/platform').rglob('*.ld')) |
                      set((ROOT / 'firmware/tools').glob('*.py')) |
                      set((ROOT / 'tests').glob('*.py')) |
                      set((ROOT / 'tests').glob('*.c')) |
                      {ROOT / 'Makefile', ROOT / 'firmware/Makefile'})
result['source_sha256'] = {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest()
                           for p in source_paths}
(ROOT / 'firmware/build/native_verification.json').write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps({k: v for k, v in result.items() if k != 'source_sha256'}, indent=2))
