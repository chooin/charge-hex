#!/usr/bin/env python3
"""Compare portable modules against protected original Thumb, without board I/O.
The only intercepted functions are the storage adapter's actual peripheral ports.
"""
import binascii
import ctypes as C
import hashlib
import json
from pathlib import Path
import random
import subprocess
import sys
import tempfile
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2,
                               UC_ARM_REG_R3, UC_ARM_REG_SP, UC_ARM_REG_LR,
                               UC_ARM_REG_PC)

if not __debug__:
    raise RuntimeError("Run verification without Python optimization (-O)")

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'recovery/tools'))
from parse_hex import parse_hex

U8, U16, U32 = C.c_uint8, C.c_uint16, C.c_uint32
PTR = C.POINTER(U8)
READ = C.CFUNCTYPE(U32, C.c_void_p, U16, PTR, U16, U32)
WRITE = READ
PROBE = C.CFUNCTYPE(U32, C.c_void_p, U32)
TICK = C.CFUNCTYPE(U32, C.c_void_p)

class Storage(C.Structure):
    _fields_ = [('context', C.c_void_p), ('read', READ), ('write', WRITE),
                ('probe', PROBE), ('tick', TICK)]

class Scenario:
    def __init__(self, fail_write=0, busy=0, tick_start=0, tick_step=1, read_status=0):
        self.events = []
        self.writes = self.probes = self.ticks = 0
        self.fail_write, self.busy = fail_write, busy
        self.start, self.step, self.read_status = tick_start, tick_step, read_status

    def read(self, address, size, timeout):
        self.events.append(('read', address, size, timeout))
        return bytes((address + i) & 255 for i in range(size)), self.read_status

    def write(self, address, data, timeout):
        self.events.append(('write', address, data.hex(), timeout))
        self.writes += 1
        return 7 if self.writes == self.fail_write else 0

    def probe(self, timeout):
        self.events.append(('probe', timeout))
        self.probes += 1
        return 3 if self.probes <= self.busy else 0

    def tick(self):
        value = (self.start + self.step * self.ticks) & 0xffffffff
        self.ticks += 1
        self.events.append(('tick', value))
        return value

raw, memory, *_ = parse_hex(ROOT / 'stm32_fw.hex')
assert hashlib.sha256(raw).hexdigest() == '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'
image = bytes(memory[a] for a in range(0x08000000, 0x08010000))
uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
uc.mem_map(0x08000000, 65536)
uc.mem_write(0x08000000, image)
uc.mem_map(0x20000000, 65536)
STOP = 0x0800f000
returned = False
scenario = None

def word(address):
    return int.from_bytes(uc.mem_read(address, 4), 'little')

def hook(engine, address, size, user):
    global returned
    if address == STOP:
        returned = True
        engine.emu_stop()
        return
    if scenario is None:
        return
    r = [engine.reg_read(reg) for reg in
         (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3)]
    sp = engine.reg_read(UC_ARM_REG_SP)
    if address in (0x08005fb8, 0x0800610c):
        assert r[0] == 0x20000b6c and r[1] == 0xa0 and r[3] == 2
        pointer, count, timeout = [word(sp + i * 4) for i in range(3)]
        if address == 0x08005fb8:
            data, result = scenario.read(r[2], count, timeout)
            if data:
                engine.mem_write(pointer, data)
        else:
            result = scenario.write(r[2], bytes(engine.mem_read(pointer, count)), timeout)
    elif address == 0x08005ea8:
        # This explicitly verifies the previously mistranslated fifth argument.
        assert r == [0x20000b6c, 0xa0, 0, 0]
        result = scenario.probe(word(sp))
    elif address == 0x08005d54:
        result = scenario.tick()
    else:
        return
    engine.reg_write(UC_ARM_REG_R0, result)
    engine.reg_write(UC_ARM_REG_PC, engine.reg_read(UC_ARM_REG_LR))

uc.hook_add(UC_HOOK_CODE, hook)

def run(address, *args):
    global returned
    returned = False
    uc.reg_write(UC_ARM_REG_SP, 0x2000f000)
    uc.reg_write(UC_ARM_REG_LR, STOP | 1)
    for reg, value in zip((UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3), args):
        uc.reg_write(reg, value)
    uc.emu_start(address | 1, 0, count=200000)
    assert returned, f'Function did not return: {address:#x}'
    return uc.reg_read(UC_ARM_REG_R0)

rng = random.Random(0xc85c)
counts = {'channel': 0, 'accounting': 0, 'crc': 0, 'storage': 0}
with tempfile.TemporaryDirectory(prefix='charge-domain-differential-') as tmp:
    library = Path(tmp) / ('domain.dylib' if sys.platform == 'darwin' else 'domain.so')
    flags = ['-dynamiclib'] if sys.platform == 'darwin' else ['-shared', '-fPIC']
    sources = [ROOT / 'firmware/src' / path for path in
               ('domain/channel.c', 'domain/timer.c', 'services/crc16.c', 'services/storage.c')]
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', *flags,
                    '-I' + str(ROOT / 'firmware/include'), *map(str, sources), '-o', str(library)], check=True)
    lib = C.CDLL(str(library))
    lib.charge_channel_set_state.argtypes = [C.POINTER(U32), PTR, U8, U8]
    lib.charge_channel_clear_accounting.argtypes = [C.c_void_p]
    lib.charge_crc16.argtypes, lib.charge_crc16.restype = [PTR, U32], U16
    lib.charge_storage_write.argtypes = [C.POINTER(Storage), U16, PTR, U16]
    lib.charge_storage_read.argtypes = [C.POINTER(Storage), U16, PTR, U16]
    lib.charge_storage_wait_ready.argtypes = [C.POINTER(Storage)]
    for channel in range(256):
        for enabled in (0, 1, 2, 255):
            bits = U32(rng.getrandbits(32))
            packed = (U8 * 3)(*(rng.randrange(256) for _ in range(3)))
            uc.mem_write(0x200000b8, bits.value.to_bytes(4, 'little'))
            uc.mem_write(0x200000dd, bytes(packed))
            lib.charge_channel_set_state(C.byref(bits), packed, channel, enabled)
            run(0x0800c85c, channel, enabled)
            assert bits.value == word(0x200000b8)
            assert bytes(packed) == bytes(uc.mem_read(0x200000dd, 3))
            counts['channel'] += 1
    for channel in range(12):
        data = bytes(rng.randrange(256) for _ in range(52))
        record = C.create_string_buffer(data, 52)
        uc.mem_write(0x200005e4 + 52 * channel, data)
        lib.charge_channel_clear_accounting(record)
        run(0x08009e14, channel)
        assert record.raw == bytes(uc.mem_read(0x200005e4 + 52 * channel, 52))
        counts['accounting'] += 1
    for size in [0, 1, 2, 9, 128, 1024] + [rng.randrange(256) for _ in range(60)]:
        data = bytes(rng.randrange(256) for _ in range(size))
        buffer = (U8 * max(1, size))(*data)
        uc.mem_write(0x20002000, data or b'\0')
        actual = lib.charge_crc16(buffer, size)
        assert actual == run(0x080001fc, 0x20002000, size) == binascii.crc_hqx(data, 0)
        counts['crc'] += 1

    def storage_case(operation, address, size, **options):
        global scenario
        host, scenario = Scenario(**options), Scenario(**options)
        data = bytes((i * 7) & 255 for i in range(max(1, size)))
        buffer = (U8 * len(data))(*data)
        uc.mem_write(0x20002000, data)
        def read_cb(context, addr, pointer, n, timeout):
            result, status = host.read(addr, n, timeout)
            if result:
                C.memmove(pointer, result, n)
            return status
        callbacks = (
            READ(read_cb),
            WRITE(lambda ctx, addr, ptr, n, timeout: host.write(addr, C.string_at(ptr, n), timeout)),
            PROBE(lambda ctx, timeout: host.probe(timeout)),
            TICK(lambda ctx: host.tick()))
        storage = Storage(None, *callbacks)
        if operation == 'wait':
            result = lib.charge_storage_wait_ready(C.byref(storage))
            original = run(0x080074c4)
        elif operation == 'write':
            result = lib.charge_storage_write(C.byref(storage), address, buffer, size)
            original = run(0x080074fc, address, 0x20002000, size)
        else:
            result = lib.charge_storage_read(C.byref(storage), address, buffer, size)
            original = run(0x08007498, address, 0x20002000, size)
            assert bytes(buffer) == bytes(uc.mem_read(0x20002000, len(data)))
        assert result == original, (operation, address, size, options, result, original)
        assert host.events == scenario.events, (operation, address, size, options, host.events, scenario.events)
        counts['storage'] += 1
        scenario = None

    for address, size in [(0,0), (0,128), (1,127), (127,258), (128,256),
                          (65535,1), (65535,2), (65408,128), (65409,128)]:
        storage_case('write', address, size)
        storage_case('read', address, size)
    for failure in (1, 2, 3, 4):
        storage_case('write', 127, 258, fail_write=failure)
    storage_case('read', 32, 4, read_status=7)
    for busy in (0, 1, 2, 3, 10):
        for start in (0, 0xffffff00):
            storage_case('wait', 0, 0, busy=busy, tick_start=start, tick_step=250)
            storage_case('write', 127, 258, busy=busy, tick_start=start, tick_step=250)

print(json.dumps({'result': 'PASS', 'cases': counts,
                  'limitations': ['Timer arithmetic uses host boundary tests, not whole-main emulation.',
                                  'I2C/tick calls are scripted ports, not electrical or IRQ validation.']}, indent=2))
