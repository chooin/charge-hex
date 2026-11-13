#!/usr/bin/env python3
"""Compile the actual recovered C and check its pure CRC against Python's independent CRC.
Only recovered_update_crc16 is called; firmware hardware functions are never executed.
"""
from pathlib import Path
import binascii
import ctypes
import re
import shutil
import subprocess
import sys
import tempfile
import json
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_SP, UC_ARM_REG_LR

source = Path(__file__).resolve().parents[1] / "reconstructed/firmware_update.c"
recovery = source.parents[1]
sys.path.insert(0, str(recovery/'tools'))
from reporting import report_path
machine = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
machine.mem_map(0x08000000, 0x10000)
machine.mem_write(0x08000000, (recovery / 'artifacts/firmware.bin').read_bytes())
machine.mem_map(0x20000000, 0x10000)
returned = False
def stop_at_return(uc, address, size, data):
    global returned
    if address == 0x0800f000:
        returned = True
        uc.emu_stop()
machine.hook_add(UC_HOOK_CODE, stop_at_return)
rows = []
compiler = shutil.which("clang") or shutil.which("cc")
assert compiler, "A host C compiler is required"
with tempfile.TemporaryDirectory(prefix="recovered-crc-") as folder:
    library = Path(folder) / ("crc.dylib" if sys.platform == "darwin" else "crc.so")
    flags = ["-dynamiclib"] if sys.platform == "darwin" else ["-shared", "-fPIC"]
    # Link-time stubs trap if any hardware dependency is accidentally called.
    stubs = Path(folder) / "hardware_stubs.c"
    declarations = re.findall(r"extern [^;]+;", source.read_text())
    stubs.write_text("#include <stdint.h>\n" + "\n".join(
        declaration.removeprefix("extern ").removesuffix(";") + " { __builtin_trap(); }"
        for declaration in declarations))
    subprocess.run([compiler, "-std=c11", *flags, str(source), str(stubs), "-o", str(library)], check=True)
    dll = ctypes.CDLL(str(library))
    crc = dll.recovered_update_crc16
    crc.argtypes = [ctypes.c_void_p, ctypes.c_uint32]
    crc.restype = ctypes.c_uint16
    samples = [b"", b"123456789", bytes(128), bytes(range(128)), bytes(range(256))*4]
    for data in samples:
        storage = ctypes.create_string_buffer(data)
        actual = crc(storage, len(data))
        expected = binascii.crc_hqx(data, 0)
        assert actual == expected, (len(data), hex(actual), hex(expected))
        if data:
            machine.mem_write(0x20002000, data)
        machine.reg_write(UC_ARM_REG_R0, 0x20002000)
        machine.reg_write(UC_ARM_REG_R1, len(data))
        machine.reg_write(UC_ARM_REG_SP, 0x2000f000)
        machine.reg_write(UC_ARM_REG_LR, 0x0800f001)
        returned = False
        machine.emu_start(0x080001fd, 0, count=1000000)
        assert returned, 'original CRC function failed to return'
        original_crc = machine.reg_read(UC_ARM_REG_R0) & 0xffff
        assert original_crc == actual, (len(data), 'original Thumb mismatch', original_crc, actual)
        rows.append({'length': len(data), 'crc': f'{actual:04X}', 'original_thumb_match': True, 'python_reference_match': True})
        print(f"length={len(data):4d} crc=0x{actual:04x} matched")
report_path('verification/update_crc_result.json').write_text(json.dumps({'result': 'PASS', 'cases': rows,
    'limitations': ['Only the pure CRC function is compared; hardware and update state machine are not executed.']}, indent=2)+'\n')
