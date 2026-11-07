#!/usr/bin/env python3
"""Unicorn differential verification of generated static C instruction semantics.
Hardware execution is never performed. No firmware calls are replaced by stubs.
"""
from pathlib import Path
import ctypes as C
import hashlib,json,random,struct,subprocess,tempfile,time
from capstone import Cs,CS_ARCH_ARM,CS_MODE_THUMB,CS_MODE_MCLASS
from capstone.arm import ARM_OP_MEM,ARM_OP_REG
from unicorn import Uc,UC_ARCH_ARM,UC_MODE_THUMB,UC_MODE_MCLASS
from unicorn.arm_const import *
HERE=Path(__file__).resolve().parent;R=HERE.parent;FLASH=0x08000000;RAM=0x20000000
B=(R/'artifacts/firmware.bin').read_bytes();rows=json.loads((R/'full_assembly/instructions.json').read_text())
REGS=[UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3,UC_ARM_REG_R4,UC_ARM_REG_R5,UC_ARM_REG_R6,UC_ARM_REG_R7,UC_ARM_REG_R8,UC_ARM_REG_R9,UC_ARM_REG_R10,UC_ARM_REG_R11,UC_ARM_REG_R12,UC_ARM_REG_SP,UC_ARM_REG_LR,UC_ARM_REG_PC]
class State(C.Structure):pass
READ=C.CFUNCTYPE(C.c_uint32,C.c_void_p,C.POINTER(State),C.c_uint32,C.c_uint)
WRITE=C.CFUNCTYPE(None,C.c_void_p,C.POINTER(State),C.c_uint32,C.c_uint,C.c_uint32)
EVENT=C.CFUNCTYPE(None,C.c_void_p,C.POINTER(State),C.c_uint,C.c_uint32)
State._fields_=[('r',C.c_uint32*16),('apsr',C.c_uint32),('pc',C.c_uint32),('primask',C.c_uint32),('stop_address',C.c_uint32),('fault_address',C.c_uint32),('fault',C.c_int32),('instructions',C.c_uint64),('flash',C.POINTER(C.c_uint8)),('sram',C.POINTER(C.c_uint8)),('sram_size',C.c_uint32),('user',C.c_void_p),('bus_read',READ),('bus_write',WRITE),('event',EVENT)]
D=Cs(CS_ARCH_ARM,CS_MODE_THUMB|CS_MODE_MCLASS);D.detail=True
rng=random.Random(0xf030c8);start=time.monotonic()
cflash=(C.c_uint8*len(B)).from_buffer_copy(B);cram=(C.c_uint8*0x10000)()
uc=Uc(UC_ARCH_ARM,UC_MODE_THUMB|UC_MODE_MCLASS);uc.mem_map(FLASH,0x20000);uc.mem_write(FLASH,B);uc.mem_map(RAM,0x10000)

def regnum(i,r):
 n=i.reg_name(r)
 return {'sp':13,'lr':14,'pc':15,'ip':12,'sb':9,'sl':10,'fp':11}.get(n,int(n[1:]) if n.startswith('r') else -1)

def setup(entry,memory,registers,apsr,primask=0):
 s=State();s.flash=cflash;s.sram=cram;s.sram_size=len(cram);s.pc=entry;s.r[:]=registers;s.apsr=apsr;s.primask=primask
 C.memmove(cram,bytes(memory),len(memory));uc.mem_write(RAM,bytes(memory))
 # Explicitly model Thread mode, MSP, no pending exceptions.
 uc.reg_write(UC_ARM_REG_CONTROL,0);uc.reg_write(UC_ARM_REG_PRIMASK,primask)
 for reg,value in zip(REGS[:-1],registers[:-1]):uc.reg_write(reg,value)
 uc.reg_write(UC_ARM_REG_XPSR,0x01000000|apsr)
 return s

def compare(s,label):
 expected=[uc.reg_read(reg) for reg in REGS[:15]]
 if list(s.r[:15])!=expected:raise AssertionError((label,'registers',[(i,hex(a),hex(b)) for i,(a,b) in enumerate(zip(s.r,expected)) if a!=b]))
 if s.pc!=uc.reg_read(UC_ARM_REG_PC):raise AssertionError((label,'pc',hex(s.pc),hex(uc.reg_read(UC_ARM_REG_PC))))
 if s.apsr&0xf0000000!=uc.reg_read(UC_ARM_REG_XPSR)&0xf0000000:raise AssertionError((label,'flags',hex(s.apsr),hex(uc.reg_read(UC_ARM_REG_XPSR))))
 if s.primask!=uc.reg_read(UC_ARM_REG_PRIMASK):raise AssertionError((label,'PRIMASK'))
 original=bytes(uc.mem_read(RAM,0x10000));translated=bytes(cram)
 if original!=translated:raise AssertionError((label,'SRAM',[hex(RAM+i) for i,(a,b) in enumerate(zip(original,translated)) if a!=b][:20]))

with tempfile.TemporaryDirectory(prefix='full-c-diff-') as tmp:
 libpath=Path(tmp)/'firmware.dylib'
 subprocess.run(['cc','-std=c11','-O0','-dynamiclib',str(HERE/'firmware_model.c'),str(HERE/'firmware_data.c'),'-o',str(libpath)],check=True)
 lib=C.CDLL(str(libpath));lib.recovered_firmware_run.argtypes=[C.POINTER(State),C.c_uint32];lib.recovered_firmware_run.restype=C.c_int
 micro=0;covered=set();memory0=rng.randbytes(0x10000)
 for row in rows:
  a=int(row['address'],16);i=next(D.disasm(B[a-FLASH:a-FLASH+4],a,count=1))
  for repeat in range(2):
   regs=[rng.getrandbits(32) for _ in range(16)];regs[13]=RAM+0xf000
   memory=bytearray(memory0);apsr=rng.randrange(16)<<28;primask=rng.randrange(2)
   for op in i.operands:
    if op.type==ARM_OP_MEM:
     base=regnum(i,op.mem.base);index=regnum(i,op.mem.index) if op.mem.index else None
     if base!=15:regs[base]=RAM+0x2000
     if index is not None:
      width={'ldr':4,'str':4,'ldrh':2,'strh':2,'ldrsh':2}.get(i.mnemonic,1)
      regs[index]=rng.randrange(64)*width
   if i.mnemonic in ('ldm','stm'):regs[regnum(i,i.operands[0].reg)]=RAM+0x3000
   if i.mnemonic in ('bx','blx'):regs[regnum(i,i.operands[0].reg)]=0x080000e5
   if i.mnemonic=='msr':regs[regnum(i,i.operands[1].reg)] &= ~3 # architecturally aligned MSP input
   if i.mnemonic=='pop':
    for index,op in enumerate(i.operands):
     if regnum(i,op.reg)==15:struct.pack_into('<I',memory,0xf000+4*index,0x080000e5)
   if i.mnemonic=='mov' and regnum(i,i.operands[0].reg)==15:regs[regnum(i,i.operands[1].reg)]=0x080000e4
   if i.mnemonic=='add' and regnum(i,i.operands[0].reg)==15:raise AssertionError('Unexpected PC add needs defined-target test setup')
   s=setup(a,memory,regs,apsr,primask)
   uc.emu_start(a|1,0,count=1)
   status=lib.recovered_firmware_run(C.byref(s),1)
   assert status==0,(hex(a),i.mnemonic,i.op_str,status,hex(s.fault_address))
   compare(s,(hex(a),i.mnemonic,i.op_str,repeat));micro+=1;covered.add(i.mnemonic)
 print('single instruction cases passed:',micro,flush=True)
 function_cases=0
 # Full execution of runtime division, CRC, parser-free state update and memory
 # helpers; nested BL, PUSH/POP, BX and switch8 execute within the model.
 cases=[]
 for _ in range(150):
  cases.append((0x080000e4,[rng.getrandbits(32),rng.randrange(1,0x100000000)],None,10000))
  cases.append((0x080040e8,[rng.getrandbits(32),rng.randrange(1,0x100000000)],None,10000))
 for length in [0,1,2,9,16,128,256,1024]:
  cases.append((0x080001fc,[RAM+0x2000,length],rng.randbytes(length),500000))
 for ch in range(256):
  for on in [0,1,2,255]:cases.append((0x0800c85c,[ch,on],None,10000))
 for ch in range(12):cases.append((0x08009e14,[ch],None,10000))
 for words in [0,1,2,32,128]:
  cases.append((0x08002cd4,[RAM+0x1000,RAM+0x2000,words*4],None,10000))
  cases.append((0x08002ce4,[0,RAM+0x2000,words*4],None,10000))
 for no,(entry,args,payload,budget) in enumerate(cases):
  memory=bytearray(memory0)
  if payload is not None:memory[0x2000:0x2000+len(payload)]=payload
  regs=[rng.getrandbits(32) for _ in range(16)];regs[13]=RAM+0xf000;regs[14]=0x08010001
  regs[:len(args)]=args
  s=setup(entry,memory,regs,0);s.stop_address=0x08010000
  uc.emu_start(entry|1,0x08010000,count=budget)
  assert uc.reg_read(UC_ARM_REG_PC)==0x08010000,('original function did not return',hex(entry))
  status=lib.recovered_firmware_run(C.byref(s),budget)
  assert status==1,(hex(entry),status,hex(s.fault_address),hex(s.pc))
  compare(s,('function',no,hex(entry)));function_cases+=1
 fault_tests=[]
 for entry,arg,expected in [(0x0800ff00,0,-1),(0x080000be,0x080000e4,-3),(0x080000be,0xfffffff9,-4)]:
  regs=[0]*16;regs[0]=arg;regs[13]=RAM+0xf000
  state=setup(entry,memory0,regs,0)
  actual=lib.recovered_firmware_run(C.byref(state),1)
  assert actual==expected,('fault boundary',entry,actual,expected)
  fault_tests.append({'entry':hex(entry),'expected':expected,'actual':actual})
 # A recognized memory load whose base is a missing peripheral must fault.
 row=next(x for x in rows if x['mnemonic']=='ldr' and x['operands']=='r0, [r0]')
 regs=[0]*16;regs[0]=0x40000000;regs[13]=RAM+0xf000
 state=setup(int(row['address'],16),memory0,regs,0)
 actual=lib.recovered_firmware_run(C.byref(state),1)
 assert actual==-2,('missing bus was silently accepted',actual)
 fault_tests.append({'entry':row['address'],'expected':-2,'actual':actual})
 # Architectural alignment boundary is checked independently of Unicorn,
 # which permits unaligned accesses in this MCLASS build. Arm DUI0662A 3.3.4
 # requires a HardFault; this model reports -5 without emulating IRQ entry.
 alignment_tests=[]
 for mnemonic,width in [('ldr',4),('str',4),('ldrh',2),('strh',2),('ldrsh',2)]:
  row=next(x for x in rows if x['mnemonic']==mnemonic and ('[r0]' in x['operands'] or '[r0, r1]' in x['operands']))
  entry=int(row['address'],16)
  for offset in range(1,width):
   for address in [RAM+0x2000+offset,0x40000000+offset]:
    regs=[0]*16;regs[0]=address;regs[13]=RAM+0xf000
    state=setup(entry,memory0,regs,0);bus_events=[]
    @READ
    def read_bus(user,ptr,a,n):bus_events.append(('read',a,n));return 0
    @WRITE
    def write_bus(user,ptr,a,n,v):bus_events.append(('write',a,n,v))
    state.bus_read=read_bus;state.bus_write=write_bus
    actual=lib.recovered_firmware_run(C.byref(state),1)
    assert actual==-5 and state.fault_address==address,(mnemonic,address,actual,state.fault_address)
    assert not bus_events,('unaligned access reached bus callback',bus_events)
    assert bytes(cram)==memory0,('unaligned access modified SRAM',mnemonic)
    alignment_tests.append({'instruction':row['address'],'access':mnemonic,'address':hex(address),'fault':actual})
 # Multiple accesses in a single LDM/STM/POP must stop bus side effects after
 # the first callback reports a fault, retaining its exact code/address.
 first_fault_tests=[]
 for mnemonic in ['ldm','stm','pop']:
  row=next(x for x in rows if x['mnemonic']==mnemonic and x['operands'].count(',')>=2)
  entry=int(row['address'],16);ins=next(D.disasm(B[entry-FLASH:entry-FLASH+4],entry,count=1))
  regs=[0]*16;regs[13]=0x40001000
  if mnemonic!='pop':regs[regnum(ins,ins.operands[0].reg)]=0x40001000
  state=setup(entry,memory0,regs,0);bus_events=[]
  @READ
  def fail_read(user,ptr,a,n):
   bus_events.append(('read',a));ptr.contents.fault=-2;ptr.contents.fault_address=a;return 0
  @WRITE
  def fail_write(user,ptr,a,n,v):
   bus_events.append(('write',a));ptr.contents.fault=-2;ptr.contents.fault_address=a
  state.bus_read=fail_read;state.bus_write=fail_write
  actual=lib.recovered_firmware_run(C.byref(state),1)
  assert actual==-2 and state.fault_address==0x40001000,(mnemonic,actual,state.fault_address)
  assert len(bus_events)==1,('additional callbacks after first fault',mnemonic,bus_events)
  first_fault_tests.append({'instruction':row['address'],'access':mnemonic,'bus_calls':len(bus_events),'fault_address':hex(state.fault_address)})
 report={'result':'PASS','single_instruction_cases':micro,'instruction_addresses_tested':len(rows),'mnemonics_tested':sorted(covered),'whole_function_cases':function_cases,'explicit_fault_boundary_tests':fault_tests,'independent_alignment_tests':alignment_tests,'first_fault_retention_tests':first_fault_tests,'firmware_sha256':hashlib.sha256(B).hexdigest(),'model_source_sha256':hashlib.sha256((HERE/'firmware_model.c').read_bytes()).hexdigest(),'elapsed_seconds':round(time.monotonic()-start,3),'method':'Generated C compiled by host compiler, differential against original Thumb via Unicorn; no function stubs','comparison':['r0..r14','PC','APSR NZCV','PRIMASK','all 64KiB test SRAM'],'limitations':['Instruction tests use aligned mapped addresses and valid Thumb branch targets, not all possible CPU states.','Alignment faults are tested independently against the architecture rule, not Unicorn, which permits those accesses.','Faults retain the first address and suppress subsequent memory/bus effects, but precise exception entry/register rollback is not modeled.','Whole-function tests cover selected pure/state routines, not complete boot/main execution.','No IRQ/exception-return, peripheral, DMA, hardware timing, or Flash-controller validation.']}
 (HERE/'verification.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
