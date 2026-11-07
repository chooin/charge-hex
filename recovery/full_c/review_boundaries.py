#!/usr/bin/env python3
"""Independent deterministic NZCV / shift-boundary differential review.

Compiles the current full C model into a temporary shared library and compares
selected original Thumb instructions against it. No imported verification module,
driver stubs, hardware access or persistent library reuse is involved.
"""
import ctypes as C
import hashlib
import itertools
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import time

import unicorn
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_MODE_MCLASS
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
    UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
    UC_ARM_REG_R12, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
    UC_ARM_REG_XPSR, UC_ARM_REG_CONTROL,
)

HERE=Path(__file__).resolve().parent
REGS=[UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3,
      UC_ARM_REG_R4,UC_ARM_REG_R5,UC_ARM_REG_R6,UC_ARM_REG_R7,
      UC_ARM_REG_R8,UC_ARM_REG_R9,UC_ARM_REG_R10,UC_ARM_REG_R11,
      UC_ARM_REG_R12,UC_ARM_REG_SP,UC_ARM_REG_LR]

class State(C.Structure):
    pass
READ=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.POINTER(State),C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.POINTER(State),C.c_uint32,C.c_uint,C.c_uint32)
EVENT=C.CFUNCTYPE(None,C.c_void_p,C.POINTER(State),C.c_uint,C.c_uint32)
State._fields_=[('r',C.c_uint32*16),('apsr',C.c_uint32),('pc',C.c_uint32),
    ('primask',C.c_uint32),('stop_address',C.c_uint32),('fault_address',C.c_uint32),
    ('fault',C.c_int32),('instructions',C.c_uint64),('flash',C.POINTER(C.c_uint8)),
    ('sram',C.POINTER(C.c_uint8)),('sram_size',C.c_uint32),('user',C.c_void_p),
    ('bus_read',READ),('bus_write',WRITE),('event',EVENT)]


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    started=time.monotonic()
    firmware_path=HERE.parent/'artifacts/firmware.bin'
    image=firmware_path.read_bytes()
    flash=(C.c_uint8*len(image)).from_buffer_copy(image)
    ram=(C.c_uint8*65536)()
    uc=Uc(UC_ARCH_ARM,UC_MODE_THUMB|UC_MODE_MCLASS)
    uc.mem_map(0x08000000,65536)
    uc.mem_write(0x08000000,image)
    uc.mem_map(0x20000000,65536)
    values=[0,1,0x7fffffff,0x80000000,0xfffffffe,0xffffffff,0x12345678]
    shift_amounts=[0,1,31,32,33,255,256,257,0xffffffff]
    cases=[
        ('LSL_register',0x080000FC,5,2,shift_amounts),
        ('LSR_register',0x080000F4,5,2,shift_amounts),
        ('ADC_register',0x08000158,5,1,values),
        ('SBC_register',0x08000136,1,3,values),
    ]
    hashes={name:digest(HERE/name) for name in ('generate.py','firmware_model.h','firmware_model.c','firmware_data.c')}
    results=[]
    with tempfile.TemporaryDirectory(prefix='firmware-independent-boundary-') as folder:
        library=Path(folder)/('model.dylib' if sys.platform=='darwin' else 'model.so')
        flags=['-dynamiclib'] if sys.platform=='darwin' else ['-shared','-fPIC']
        subprocess.run(['cc','-std=c11','-O0',*flags,str(HERE/'firmware_model.c'),str(HERE/'firmware_data.c'),'-o',str(library)],check=True)
        dll=C.CDLL(str(library))
        dll.recovered_firmware_run.argtypes=[C.POINTER(State),C.c_uint32]
        dll.recovered_firmware_run.restype=C.c_int
        for name,entry,operand_register,amount_register,other_values in cases:
            count=0
            for operand,amount,flags in itertools.product(values,other_values,range(16)):
                state=State()
                state.flash=flash
                state.sram=ram
                state.sram_size=len(ram)
                state.pc=entry
                state.r[13]=0x20008000
                state.r[operand_register]=operand
                state.r[amount_register]=amount
                state.apsr=flags<<28
                for register,value in zip(REGS,state.r):
                    uc.reg_write(register,value)
                uc.reg_write(UC_ARM_REG_XPSR,0x01000000|(flags<<28))
                uc.reg_write(UC_ARM_REG_CONTROL,0)
                uc.emu_start(entry|1,0,count=1)
                assert dll.recovered_firmware_run(C.byref(state),1)==0,(name,'model status')
                expected=[uc.reg_read(register) for register in REGS]
                assert list(state.r[:15])==expected,(name,hex(operand),hex(amount),flags,'registers')
                assert state.pc==uc.reg_read(UC_ARM_REG_PC),(name,'PC')
                assert state.apsr&0xf0000000==uc.reg_read(UC_ARM_REG_XPSR)&0xf0000000,(name,hex(operand),hex(amount),flags,'NZCV')
                count+=1
            results.append({'group':name,'original_address':hex(entry),'cases':count,'result':'PASS'})
    assert hashes=={name:digest(HERE/name) for name in hashes},'Sources changed during verification; rerun against stable files'
    report={'result':'PASS','total_cases':sum(r['cases'] for r in results),'groups':results,
        'firmware_sha256':digest(firmware_path),'source_sha256':hashes,
        'unicorn_version':unicorn.__version__,'compiler':subprocess.run(['cc','--version'],capture_output=True,text=True,check=True).stdout.splitlines()[0],
        'tested_operands':[hex(n) for n in values],'tested_shift_register_values':[hex(n) for n in shift_amounts],
        'initial_nzcv_patterns':16,'elapsed_seconds':round(time.monotonic()-started,3),
        'limitations':['Tests only four representative instruction addresses and listed values, not a complete architecture proof.',
            'No memory alignment, peripheral, fault-delivery, interrupt, or hardware timing semantics are exercised here.',
            'Unicorn is not used as authority for unaligned Cortex-M0+ memory access or low-bit MSP behavior.']}
    (HERE/'review_boundaries.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps(report,indent=2))


if __name__=='__main__':
    main()
