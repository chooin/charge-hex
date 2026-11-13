#!/usr/bin/env python3
"""Original main Thumb vs complete explicit C lift under identical mocked callees.
Only main's CFG is executed. No board/IO effects, real callee behavior or IRQs.
"""
from pathlib import Path
import ctypes as C
import json,hashlib,random,subprocess,tempfile,struct,sys
from unicorn import Uc,UC_ARCH_ARM,UC_MODE_THUMB,UC_MODE_MCLASS,UC_HOOK_CODE
from unicorn.arm_const import *
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'tools'))
from reporting import report_path
B=(R/'artifacts/firmware.bin').read_bytes()
COVER=json.loads((R/'artifacts/application_main_coverage.json').read_text())
INS={int(x['address'],16) for x in COVER['instructions']}
EXT={int(x,16) for x in COVER['external_calls']}
REGS=[UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3,UC_ARM_REG_R4,UC_ARM_REG_R5,UC_ARM_REG_R6,UC_ARM_REG_R7,UC_ARM_REG_R8,UC_ARM_REG_R9,UC_ARM_REG_R10,UC_ARM_REG_R11,UC_ARM_REG_R12,UC_ARM_REG_SP,UC_ARM_REG_LR,UC_ARM_REG_PC]
FLASH,RAM=0x08000000,0x20000000
class State(C.Structure):pass
CALL=C.CFUNCTYPE(C.c_int,C.c_void_p,C.c_uint32,C.POINTER(State))
READ=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.c_uint32,C.c_uint,C.c_uint32)
State._fields_=[('r',C.c_uint32*16),('apsr',C.c_uint32),('pc',C.c_uint32),('fault_address',C.c_uint32),('fault',C.c_int32),('main_instruction_count',C.c_uint64),('flash',C.POINTER(C.c_uint8)),('sram',C.POINTER(C.c_uint8)),('sram_size',C.c_uint32),('user',C.c_void_p),('call',CALL),('io_read',READ),('io_write',WRITE)]
rng=random.Random(0xa708)

def calls_effect(target,regs,flags,scenario):
    # Explicit mock model: deterministic event hooks; all caller-saved outputs
    # remain unchanged unless listed. This is not an implementation of drivers.
    if target==0x80040e8:
        num,den=regs[0],regs[1]
        regs[0]=num//den if den else 0
        regs[1]=num%den if den else num
    elif target==0x800a6cc:regs[0]=scenario['now']
    elif target==0x8008278:regs[0]=scenario['measurement']
    elif target in (0x800a068,0x8009fec,0x800a018,0x800a128):regs[0]=scenario['result_bit']
    elif target in (0x800a2d0,0x8005d3c):regs[0]=0 # No pressed keys, output-busy low
    else:regs[0]=0
    return regs,flags

def initial_memory(seed):
    mem=bytearray(0x10000)
    mem[0xb4:0x144]=B[0xce98:0xcf28]
    struct.pack_into('<I',mem,0xbc8,0x40012c00)
    # Avoid unrealistic underflowed configuration indices; exercise values
    # through scenarios below rather than randomizing pointers arbitrarily.
    return mem

def run_pair(lib,entry,mem,regs,flags,scenario,budget=20000,stop=0x800a7d4):
    cflash=(C.c_uint8*len(B)).from_buffer_copy(B)
    cram=(C.c_uint8*len(mem)).from_buffer_copy(mem)
    cs=State();cs.r[:]=regs;cs.apsr=flags;cs.pc=entry
    cs.flash=cflash;cs.sram=cram;cs.sram_size=len(mem)
    uc=Uc(UC_ARCH_ARM,UC_MODE_THUMB|UC_MODE_MCLASS)
    uc.mem_map(FLASH,0x10000);uc.mem_write(FLASH,B)
    uc.mem_map(RAM,0x10000);uc.mem_write(RAM,bytes(mem))
    uc.mem_map(0x40000000,0x30000)
    uc.mem_map(0x48000000,0x1000)
    for reg,value in zip(REGS,regs):uc.reg_write(reg,value)
    uc.reg_write(UC_ARM_REG_XPSR,0x01000000|flags)
    cevents=[];uevents=[];trace=set();counter=0;first=True;c_io={}
    # Compare arguments plus eight stack words because several main calls pass
    # arguments beyond r0..r3. This exposes ABI drift hidden by C prototypes.
    def event(target,rr,ap,read):
        stack=bytes(read(rr[13],32))
        return [hex(target),rr[:4],rr[12],rr[14],ap&0xf0000000,stack.hex()]
    @CALL
    def cb(user,target,ptr):
        s=ptr.contents;rr=list(s.r);cevents.append(event(target,rr,s.apsr,lambda a,n:bytes(cram[a-RAM:a-RAM+n])))
        rr,ap=calls_effect(target,rr,s.apsr,scenario);s.r[:]=rr;s.apsr=ap
        return 1 # yield at every external call so stop boundaries are visible
    @READ
    def rd(user,address,width):return sum(c_io.get(address+i,0)<<(8*i) for i in range(width))
    @WRITE
    def wr(user,address,width,value):
        for i in range(width):c_io[address+i]=(value>>(8*i))&255
    cs.call=cb;cs.io_read=rd;cs.io_write=wr
    def hook(machine,address,size,user):
        nonlocal first,counter
        if address==stop and not first:
            machine.emu_stop();return
        first=False
        if address in INS:trace.add(address);counter+=1
        if address in EXT:
            rr=[machine.reg_read(reg) for reg in REGS];ap=machine.reg_read(UC_ARM_REG_XPSR)
            uevents.append(event(address,rr,ap,lambda a,n:machine.mem_read(a,n)))
            rr,ap=calls_effect(address,rr,ap,scenario)
            for reg,value in zip(REGS[:-1],rr[:-1]):machine.reg_write(reg,value)
            machine.reg_write(UC_ARM_REG_XPSR,0x01000000|ap)
            machine.reg_write(UC_ARM_REG_PC,rr[14])
    uc.hook_add(UC_HOOK_CODE,hook)
    uc.emu_start(entry|1,0,count=budget)
    upc=uc.reg_read(UC_ARM_REG_PC)
    assert upc==stop,(hex(upc),'original failed to reach boundary')
    # End exactly at same main instruction count. Helper instructions do not
    # count toward the C budget; switch helper is inlined as one main BL.
    while cs.main_instruction_count<counter:
        status=lib.recovered_application_main_run(C.byref(cs),counter-cs.main_instruction_count)
        assert status>=0,(status,hex(cs.fault_address))
    if cs.pc!=stop:
        # Last instruction at B0C4 is an internal BL; budget reaches next STEP.
        status=lib.recovered_application_main_run(C.byref(cs),0)
        assert status>=0
    assert cs.pc==upc,(hex(cs.pc),hex(upc),'pc')
    original=bytes(uc.mem_read(RAM,0x10000));translated=bytes(cram)
    for address,value in c_io.items():assert bytes(uc.mem_read(address,1))==bytes([value]),('MMIO',hex(address))
    # helper scratch below main SP is architecturally observable; model writes
    # it too. Compare SRAM and retained main stack, except untouched CPU context.
    if original!=translated:
        dif=[hex(RAM+i) for i,(x,y) in enumerate(zip(original,translated)) if x!=y]
        raise AssertionError(('ram',dif[:20]))
    assert cevents==uevents,('events',next(((i,a,b) for i,(a,b) in enumerate(zip(cevents,uevents)) if a!=b),None),len(cevents),len(uevents))
    uregs=[uc.reg_read(r) for r in REGS]
    assert list(cs.r[:15])==uregs[:15],('registers',list(cs.r[:15]),uregs[:15])
    assert cs.apsr&0xf0000000==uc.reg_read(UC_ARM_REG_XPSR)&0xf0000000,('APSR',hex(cs.apsr),hex(uc.reg_read(UC_ARM_REG_XPSR)))
    return translated,uregs,uc.reg_read(UC_ARM_REG_XPSR)&0xf0000000,trace,len(uevents)

with tempfile.TemporaryDirectory(prefix='main-lift-check-') as temp:
    libpath=Path(temp)/'main.dylib'
    subprocess.run(['cc','-std=c11','-O2','-dynamiclib','-Wall','-Wextra','-Werror',str(R/'reconstructed/application_main.c'),'-o',str(libpath)],check=True)
    lib=C.CDLL(str(libpath));lib.recovered_application_main_run.argtypes=[C.POINTER(State),C.c_uint32]
    lib.recovered_application_main_run.restype=C.c_int
    cases=0;coverage=set();call_count=0
    regs=[0]*16;regs[13]=RAM+0xf000;flags=0
    sc={'now':100,'measurement':0,'result_bit':0}
    memory,regs,flags,visited,n=run_pair(lib,0x800a708,initial_memory(0),regs,flags,sc)
    cases+=1;coverage|=visited;call_count+=n
    base_memory,base_regs,base_flags=memory,regs,flags
    scenarios=[]
    # Every timer index gets a separate expiry case, as well as non-expiry
    # behavior, alternate global mode and active channel states.
    for timer in range(93):
        scenarios.append({'timer':timer,'expiry':True,'mode':timer%6,'state':timer%5,'metric':timer*30,'result_bit':timer&1})
        scenarios.append({'timer':timer,'expiry':False,'mode':timer%6,'state':timer%5,'metric':timer*30,'result_bit':timer&1})
    for _ in range(160):
        scenarios.append({'timer':rng.randrange(93),'expiry':rng.choice([True,False]),'mode':rng.randrange(6),'state':rng.randrange(5),'metric':rng.randrange(4000),'result_bit':rng.randrange(2)})
    for no,spec in enumerate(scenarios):
        mem=bytearray(base_memory);rr=list(base_regs)
        struct.pack_into('<H',mem,0x8d4+spec['timer']*2,1 if spec['expiry'] else 100)
        mem[0x854]=spec['mode'];mem[0x855]=no%12
        for off,value in [(12,100),(14,500),(16,1000),(18,2000),(20,100),(22,120),(24,140),(26,1),(28,1),(30,100),(32,30),(34,1),(36,spec['mode']%4),(38,60),(40,50)]:struct.pack_into('<H',mem,0x854+off,value)
        for ch in range(12):
            at=0x5e4+52*ch
            struct.pack_into('<I',mem,at,60+ch if no%3 else 0)
            struct.pack_into('<H',mem,at+4,spec['metric'])
            mem[at+21]=1+ch%3;mem[at+22]=spec['state'];mem[at+44]=ch%4
        sc={'now':101,'measurement':spec['metric'],'result_bit':spec['result_bit']}
        _,_,_,visited,n=run_pair(lib,0x800a7d4,mem,rr,base_flags,sc)
        cases+=1;coverage|=visited;call_count+=n
    report={'result':'PASS','method':'Original Thumb main versus explicit compiled C lift, identical mocked external-call register effects','cases':cases,'main_instruction_count':len(INS),'executed_instruction_addresses':len(coverage),'instruction_coverage_fraction':len(coverage)/len(INS),'external_call_events_compared':call_count,'source_sha256':hashlib.sha256((R/'reconstructed/application_main.c').read_bytes()).hexdigest(),'uncovered_addresses':[hex(x) for x in sorted(INS-coverage)],'limitations':['External functions are mock callbacks, not real driver or business implementations.','No interrupts, hardware timing, input press loops, or asynchronous mutation modeled.','Full static CFG emitted; finite dynamic coverage does not prove every possible state.']}
    report_path('verification/application_main_result.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:v for k,v in report.items() if k!='uncovered_addresses'},indent=2))
