#!/usr/bin/env python3
"""Differential checks: reconstructed C versus original Thumb via Unicorn.
No board/peripheral execution. External dispatch/TX calls intercepted as stubs.
Requires a C compiler, Python unicorn, and the extracted firmware.bin.
"""
import ctypes as C
import json
from pathlib import Path
import random
import subprocess
import sys
import tempfile
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_HOOK_CODE
from unicorn.arm_const import UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'recovery/tools'))
from reporting import report_path
rng = random.Random(0x8EAC)
binary = (ROOT/'recovery/artifacts/firmware.bin').read_bytes()
STOP = 0x0800F000
uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB)
uc.mem_map(0x08000000, 0x10000)
uc.mem_write(0x08000000, binary)
uc.mem_map(0x20000000, 0x10000)
calls = []
stopped = False

def hook(engine, address, size, user):
    global stopped
    if address == STOP:
        stopped = True
        engine.emu_stop()
    elif address in [0x08009694,0x0800C830,0x0800947C]:
        calls.append((address, engine.reg_read(UC_ARM_REG_R0), engine.reg_read(UC_ARM_REG_R1)))
        engine.reg_write(UC_ARM_REG_PC, engine.reg_read(UC_ARM_REG_LR))
uc.hook_add(UC_HOOK_CODE,hook)

def run(address, *args):
    global stopped
    calls.clear()
    stopped = False
    uc.reg_write(UC_ARM_REG_SP,0x2000F000)
    uc.reg_write(UC_ARM_REG_LR,STOP|1)
    for reg,arg in zip([UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3],args):
        uc.reg_write(reg,arg)
    uc.emu_start(address|1, 0, count=100000)
    assert stopped, f'emulation did not return: {address:#x}'

with tempfile.TemporaryDirectory(prefix='firmware-serial-check-') as tmp:
    tmp = Path(tmp)
    stub = tmp/'stubs.c'
    stub.write_text('''#include <stdint.h>
int fixed55_calls, fixed44_calls;
void serial_on_fixed55(void){fixed55_calls++;}
void serial_on_fixed44(const uint8_t *p){(void)p;fixed44_calls++;}
void serial_on_block(const uint8_t *p){(void)p;}
int fw_08007280_uart_transmit_dma(void *h,const uint8_t*d,uint16_t n){(void)h;(void)d;(void)n;return 1;}
void fw_0800cdb8_event(uint8_t e){(void)e;}
''')
    libpath = tmp/'serial.dylib'
    subprocess.run(['cc','-dynamiclib','-std=c11','-Wall','-Wextra','-Werror',str(ROOT/'recovery/reconstructed/serial_protocol.c'),str(stub),'-o',str(libpath)], check=True)
    lib=C.CDLL(str(libpath))
    U8=C.c_uint8
    class Parser(C.Structure): _fields_=[('mode',U8),('expected',U8),('index',U8)]
    lib.serial_feed_byte.argtypes=[C.POINTER(Parser),C.POINTER(U8),U8]
    lib.serial_build_frame.argtypes=[C.POINTER(U8),U8,U8,U8,C.POINTER(U8),U8]
    lib.serial_build_frame.restype=C.c_uint16
    lib.serial_apply_parameter_payload.argtypes=[C.POINTER(U8),C.POINTER(U8),U8]
    s=Parser();buf=(U8*256)()
    uc.mem_write(0x20000124,b'\0'*3)
    uc.mem_write(0x20001024,b'\0'*256)
    streams=[]
    for _ in range(100):
        for header,length in [(0x55,9),(0x44,27)]:
            frame=[header,0xaa]+[rng.randrange(256) for _ in range(length-3)]
            x=0
            for b in frame:x^=b
            streams.extend(frame+[x])
            streams.extend(frame+[x^1])
        streams.extend([0xaa,5,1,2,3,4,5,0x55,3,1,2,3])
    streams += [rng.randrange(256) for _ in range(2000)]
    for ordinal,byte in enumerate(streams):
        before55=C.c_int.in_dll(lib,'fixed55_calls').value
        before44=C.c_int.in_dll(lib,'fixed44_calls').value
        lib.serial_feed_byte(C.byref(s),buf,byte)
        run(0x08008EAC,byte)
        assert bytes(s)==bytes(uc.mem_read(0x20000124,3)), ('state',ordinal)
        assert bytes(buf)==bytes(uc.mem_read(0x20001024,256)), ('buffer',ordinal)
        expected=[]
        if C.c_int.in_dll(lib,'fixed55_calls').value!=before55:expected.append(0x08009694)
        if C.c_int.in_dll(lib,'fixed44_calls').value!=before44:expected.append(0x0800C830)
        assert expected==[c[0] for c in calls], ('dispatch',ordinal)
        if expected==[0x0800C830]:assert calls[0][1]==0x20001027
    for n in range(256):
        payload=bytes(rng.randrange(256) for _ in range(n))
        p=(U8*max(n,1))(*payload)
        out=(U8*256)(*([0x5a]*256))
        command,subcommand,prefix=[rng.randrange(256) for _ in range(3)]
        count=lib.serial_build_frame(out,command,n,subcommand,p,prefix)
        uc.mem_write(0x20000A18,b'\x5a'*256)
        uc.mem_write(0x20002000,payload or b'\0')
        uc.mem_write(0x2000F000,prefix.to_bytes(4,'little'))
        run(0x0800C7C4,command,n,subcommand,0x20002000)
        assert bytes(out)==bytes(uc.mem_read(0x20000A18,256)),('TX bytes',n)
        assert ([c[2] for c in calls] == [count] if count else not calls), ('TX length',n)
    for trial in range(200):
        payload=bytes(rng.randrange(256) for _ in range(23))
        config=bytes(rng.randrange(256) for _ in range(120))
        endian=trial%3
        p=(U8*23)(*payload); c=(U8*120)(*config)
        lib.serial_apply_parameter_payload(c,p,endian)
        uc.mem_write(0x20002000,payload);uc.mem_write(0x20000854,config)
        run(0x0800BCD8,0x20002000,endian)
        actual=bytes(uc.mem_read(0x20000854,120))
        assert bytes(c)==actual,('config',trial,[(i,x,y) for i,(x,y) in enumerate(zip(bytes(c),actual)) if x!=y])
    result={'parser_byte_steps':len(streams),'tx_payload_lengths':256,'parameter_payload_cases':200,
            'result':'PASS','method':'compiled reconstructed C differential against original Thumb via Unicorn 2.1.4',
            'limitations':['External frame dispatch and TX calls are intercepted, not emulated.',
                           'No hardware, DMA, peripheral timing, interrupt concurrency, or full application equivalence verified.',
                           'Parser buffer mapped as 256 bytes to observe malformed-input semantics; not a claim of firmware allocation.']}
    report_path('verification/serial_result.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result,indent=2))
