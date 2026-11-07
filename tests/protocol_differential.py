#!/usr/bin/env python3
"""Execute the new portable C against original HEX Thumb instructions.

External dispatch and TX are observed at their call boundaries. This does not
model hardware, DMA, interrupt concurrency, or the full application.
"""
import ctypes as C
import hashlib
import json
import os
from pathlib import Path
import random
import subprocess
import sys
import tempfile

from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
)

if not __debug__:
    raise RuntimeError("Run verification without Python optimization (-O)")

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'recovery/tools'))
from parse_hex import parse_hex

raw, memory, *_ = parse_hex(ROOT / 'stm32_fw.hex')
assert hashlib.sha256(raw).hexdigest() == '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'
binary = bytes(memory[a] for a in range(0x08000000, 0x08010000))
rng = random.Random(0x8EAC)
STOP = 0x0800F000
uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
uc.mem_map(0x08000000, 0x10000)
uc.mem_write(0x08000000, binary)
uc.mem_map(0x20000000, 0x10000)
calls = []
stopped = False


def hook(engine, address, _size, _user):
    global stopped
    if address == STOP:
        stopped = True
        engine.emu_stop()
    elif address in [0x08009694, 0x0800C830, 0x0800947C, 0x0800B0DC]:
        calls.append((address, engine.reg_read(UC_ARM_REG_R0), engine.reg_read(UC_ARM_REG_R1)))
        engine.reg_write(UC_ARM_REG_PC, engine.reg_read(UC_ARM_REG_LR))


uc.hook_add(UC_HOOK_CODE, hook)


def run(address, *args):
    global stopped
    calls.clear()
    stopped = False
    uc.reg_write(UC_ARM_REG_SP, 0x2000F000)
    uc.reg_write(UC_ARM_REG_LR, STOP | 1)
    for reg, arg in zip([UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3], args):
        uc.reg_write(reg, arg)
    uc.emu_start(address | 1, 0, count=100000)
    assert stopped, f'emulation did not return: {address:#x}'


with tempfile.TemporaryDirectory(prefix='charge-protocol-') as tmp:
    libpath = Path(tmp) / ('protocol.dylib' if sys.platform == 'darwin' else 'protocol.so')
    compile_args = ['-dynamiclib'] if sys.platform == 'darwin' else ['-shared', '-fPIC']
    subprocess.run([os.environ.get('CC', 'cc'), *compile_args, '-std=c11', '-Wall', '-Wextra', '-Werror',
                    '-I', str(ROOT / 'firmware/include'),
                    str(ROOT / 'firmware/src/protocol/serial.c'),
                    str(ROOT / 'firmware/src/domain/config.c'), '-o', str(libpath)], check=True)
    lib = C.CDLL(str(libpath))
    U8 = C.c_uint8
    P8 = C.POINTER(U8)

    class Parser(C.Structure):
        _fields_ = [('mode', U8), ('expected', U8), ('index', U8)]

    lib.charge_serial_feed.argtypes = [C.POINTER(Parser), P8, U8]
    lib.charge_serial_feed.restype = C.c_int
    lib.charge_serial_build_frame.argtypes = [P8, C.c_size_t, U8, U8, U8, P8, U8]
    lib.charge_serial_build_frame.restype = C.c_uint16
    lib.charge_serial_build_identifier_response.argtypes = [P8, C.c_size_t, P8, P8]
    lib.charge_serial_build_identifier_response.restype = C.c_uint16
    lib.charge_serial_block_valid.argtypes = [P8, C.c_uint16]
    lib.charge_serial_block_valid.restype = C.c_bool
    lib.charge_config_apply_payload.argtypes = [P8, P8, U8]
    lib.charge_config_apply_payload.restype = None
    state = Parser()
    buffer = (U8 * 256)()
    uc.mem_write(0x20000124, b'\0' * 3)
    uc.mem_write(0x20001024, b'\0' * 256)
    stream = []
    for _ in range(100):
        for header, length in [(0x55, 9), (0x44, 27)]:
            frame = [header, 0xaa] + [rng.randrange(256) for _ in range(length - 3)]
            checksum = 0
            for byte in frame:
                checksum ^= byte
            stream.extend(frame + [checksum])
            stream.extend(frame + [checksum ^ 1])
        stream.extend([0xaa, 5, 1, 2, 3, 4, 5, 0x55, 3, 1, 2, 3])
    stream += [rng.randrange(256) for _ in range(2000)]
    # Exercise all dynamic lengths, including expected-length and index wraps.
    stream += [0] * 256
    for length in range(256):
        stream += [0xaa, length] + [0] * 256
    for ordinal, byte in enumerate(stream):
        event = lib.charge_serial_feed(C.byref(state), buffer, byte)
        run(0x08008EAC, byte)
        assert bytes(state) == bytes(uc.mem_read(0x20000124, 3)), ('state', ordinal)
        assert bytes(buffer) == bytes(uc.mem_read(0x20001024, 256)), ('buffer', ordinal)
        expected = {0: [], 1: [0x08009694], 2: [0x0800C830]}[event]
        assert expected == [call[0] for call in calls], ('dispatch', ordinal)
        if event == 2:
            assert calls[0][1] == 0x20001027

    for n in range(256):
        payload = bytes(rng.randrange(256) for _ in range(n))
        p = (U8 * max(n, 1))(*payload)
        out = (U8 * 256)(*([0x5a] * 256))
        command, subcommand, prefix = [rng.randrange(256) for _ in range(3)]
        count = lib.charge_serial_build_frame(out, len(out), command, n, subcommand, p, prefix)
        uc.mem_write(0x20000A18, b'\x5a' * 256)
        uc.mem_write(0x20002000, payload or b'\0')
        uc.mem_write(0x2000F000, prefix.to_bytes(4, 'little'))
        run(0x0800C7C4, command, n, subcommand, 0x20002000)
        assert bytes(out) == bytes(uc.mem_read(0x20000A18, 256)), ('TX bytes', n)
        assert [call[2] for call in calls] == ([count] if count else []), ('TX length', n)

    for mode in range(256):
        identifier = bytes(rng.randrange(256) for _ in range(4))
        record = bytes([mode, rng.randrange(256), rng.randrange(256)])
        out = (U8 * 32)(*([0x5a] * 32))
        count = lib.charge_serial_build_identifier_response(out, len(out), (U8 * 4)(*identifier), (U8 * 3)(*record))
        uc.mem_write(0x20000A18, b'\x5a' * 32)
        uc.mem_write(0x20002000, identifier)
        uc.mem_write(0x20002010, record)
        run(0x0800964E, 0x20002000, 0x20002010)
        assert bytes(out) == bytes(uc.mem_read(0x20000A18, 32)), ('identifier', mode)
        assert [call[2] for call in calls] == ([count] if count else [])

    for trial in range(600):
        payload = bytes(rng.randrange(256) for _ in range(23))
        config = bytes(rng.randrange(256) for _ in range(120))
        endian = trial % 3
        p = (U8 * 23)(*payload)
        c = (U8 * 120)(*config)
        lib.charge_config_apply_payload(c, p, endian)
        uc.mem_write(0x20002000, payload)
        uc.mem_write(0x20000854, config)
        run(0x0800BCD8, 0x20002000, endian)
        assert bytes(c) == bytes(uc.mem_read(0x20000854, 120)), ('config', trial)

    for length in range(2, 258):
        frame = bytearray(rng.randrange(256) for _ in range(length))
        checksum = 0
        for byte in frame[1:-1]:
            checksum ^= byte
        for valid in (True, False):
            frame[-1] = checksum if valid else checksum ^ 1
            actual = lib.charge_serial_block_valid((U8 * length)(*frame), length)
            uc.mem_write(0x20002000, bytes(frame))
            run(0x08008E84, 0x20002000, length)
            assert actual == valid == bool(calls), ('block', length, valid)
            if valid:
                assert calls == [(0x0800B0DC, 0x20002000, uc.reg_read(UC_ARM_REG_R1))]

    print(json.dumps({
        'result': 'PASS', 'parser_byte_steps': len(stream),
        'tx_payload_lengths': 256, 'identifier_modes': 256,
        'parameter_payload_cases': 600, 'block_checksum_cases': 512,
        'oracle': 'original protected HEX executed by Unicorn',
        'limitations': ['External dispatch/TX calls intercepted.',
                        'No hardware, DMA, IRQ concurrency, or full application verification.',
                        '256-byte parser test storage is not the original MCU allocation.'],
    }, indent=2))
