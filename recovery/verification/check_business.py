#!/usr/bin/env python3
"""Original Thumb versus recompiled manual business C, with deterministic opaque callees."""
from pathlib import Path
import subprocess,tempfile,re,struct,json,random,hashlib,sys
from unicorn import Uc,UC_ARCH_ARM,UC_MODE_THUMB,UC_MODE_MCLASS,UC_HOOK_CODE
from unicorn.arm_const import *
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'recovery/tools'))
from reporting import report_path
SRC=ROOT/'recovery/reconstructed/business_handlers.c'
FW=(ROOT/'recovery/artifacts/firmware.bin').read_bytes()
F=0x08000000; C=0x08100000; R=0x20000000; STOP=0x0801f000
regs=[UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3]
externs={int(x,16):'bh_'+x for x in re.findall(r'extern\s+\w+\s+bh_([0-9a-f]+)',SRC.read_text())}
rng=random.Random(0xB0DC)
class Machine:
 def __init__(self,blob,base,hooks):
  self.u=Uc(UC_ARCH_ARM,UC_MODE_THUMB|UC_MODE_MCLASS);self.u.mem_map(F,0x20000)
  if base!=F:self.u.mem_map(base,0x10000)
  self.u.mem_write(base,blob);self.u.mem_map(R,0x10000);self.hooks=hooks
  self.visited=set();self.u.hook_add(UC_HOOK_CODE,self.hook)
 def hook(self,u,addr,size,data):
  self.visited.add(addr)
  if addr==STOP:self.done=True;u.emu_stop();return
  if addr not in self.hooks:return
  original=self.hooks[addr];a=[u.reg_read(x) for x in regs];sp=u.reg_read(UC_ARM_REG_SP)
  fifth=struct.unpack('<I',u.mem_read(sp,4))[0];ret=0;ev=[hex(original)]
  if original==0x0800c7c4: ev += [a[0],a[1],a[2],fifth,bytes(u.mem_read(a[3],a[1])).hex()]
  elif original==0x0800ca80:ev += a+[fifth];ret=(a[0]^a[1]^a[2]^a[3]^fifth)&255
  elif original==0x0800b74c:
   ev += [a[0]]
   for p,v in zip(a[1:]+[fifth],[0x1234,0x2345,0x3456,0x4567]):u.mem_write(p,struct.pack('<I',v))
   ret=a[0]%12+1
  elif original==0x0800b6d4:ev+=a[:2];u.mem_write(a[2],struct.pack('<I',0x6d4))
  elif original in [0x0800bc38,0x0800b708,0x0800b7a8]:
   n={0x0800bc38:6,0x0800b708:25,0x0800b7a8:23}[original]
   blob=bytes([5]+list(range(1,n)));u.mem_write(a[0],blob)
  elif original in [0x0800be24,0x0800c20c,0x0800c1c8,0x0800bcd8]:
   ev += [bytes(u.mem_read(a[0],23)).hex()]
   if original==0x0800bcd8:ev += [a[1]]
  elif original in [0x0800a4a8,0x0800a4b4,0x08009e30,0x0800bcac,0x0800bc74]:ev+=a[:2]
  elif original in [0x0800cd40,0x08009d04]:ev += a[:1];ret=1
  elif original in [0x0800cdb8,0x0800cc44]:ev+=a[:1]
  elif original==0x080094b4:ev += [a[1],bytes(u.mem_read(a[0],a[1])).hex()]
  elif original==0x0800964e:ev += [bytes(u.mem_read(a[0],4)).hex(),bytes(u.mem_read(a[1],3)).hex()]
  elif original in [0x080063ec,0x0800a65c]:pass
  else:raise AssertionError(hex(original))
  self.events.append(ev);u.reg_write(UC_ARM_REG_R0,ret);u.reg_write(UC_ARM_REG_PC,u.reg_read(UC_ARM_REG_LR))
 def call(self,entry,mem,args,scratch):
  self.u.mem_write(R,mem);self.u.mem_write(R+0xe000,bytes(0x2000))
  # Original B0DC reply scratch = incoming SP - 20 saved regs - 92 locals + 4.
  self.u.mem_write(R+0xf000-108,scratch)
  self.u.mem_write(R+0x3000,scratch)
  for r in [UC_ARM_REG_R0,UC_ARM_REG_R1,UC_ARM_REG_R2,UC_ARM_REG_R3,UC_ARM_REG_R4,UC_ARM_REG_R5,UC_ARM_REG_R6,UC_ARM_REG_R7,UC_ARM_REG_R12]:self.u.reg_write(r,0)
  for r,a in zip(regs,args):self.u.reg_write(r,a)
  self.u.reg_write(UC_ARM_REG_SP,R+0xf000);self.u.reg_write(UC_ARM_REG_LR,STOP|1)
  self.events=[];self.done=False;self.u.emu_start(entry|1,STOP+2,count=300000)
  assert self.done,hex(self.u.reg_read(UC_ARM_REG_PC))
  return bytes(self.u.mem_read(R,0x2000)),self.events

def put16(m,o,v):struct.pack_into('<H',m,o,v)
def put32(m,o,v):struct.pack_into('<I',m,o,v)
with tempfile.TemporaryDirectory(prefix='business-diff-') as t:
 t=Path(t);st=t/'stub.S';st.write_text('.syntax unified\n.thumb\n'+''.join(f'.global {n}\n.thumb_func\n{n}:\n bx lr\n' for n in externs.values()))
 elf=t/'business.elf';binary=t/'business.bin'
 subprocess.run(['arm-none-eabi-gcc','-mcpu=cortex-m0plus','-mthumb','-O2','-ffreestanding','-fno-builtin','-ffunction-sections','-nostdlib','-Wl,--gc-sections','-Wl,-Ttext=0x08100000','-Wl,-e,recovered_dispatch_command','-Wl,--undefined=recovered_handle_identifier_frame',str(SRC),str(st),'-lgcc','-o',str(elf)],check=True)
 subprocess.run(['arm-none-eabi-objcopy','-O','binary',str(elf),str(binary)],check=True)
 symbols={p[2]:int(p[0],16) for l in subprocess.check_output(['arm-none-eabi-nm',str(elf)],text=True).splitlines() if len(p:=l.split())==3}
 orig=Machine(FW,F,{a:a for a in externs});new=Machine(binary.read_bytes(),C,{symbols[n]:a for a,n in externs.items()})
 counts={'dispatcher':0,'identifier':0};fails=[]
 def compare(kind,entry,symbol,m,args,label):
  scratch=rng.randbytes(60);x=orig.call(entry,bytes(m),args,scratch);y=new.call(symbols[symbol],bytes(m),args+([R+0x3000] if kind=='dispatcher' else []),scratch)
  counts[kind]+=1
  if x!=y:
   diff=[hex(R+i) for i,(a,b) in enumerate(zip(x[0],y[0])) if a!=b]
   fails.append({'kind':kind,'label':label,'memory_diff':diff[:30],'original_events':x[1],'c_events':y[1]})
   if len(fails)>=5:raise RuntimeError(json.dumps(fails,indent=2))
 for header in [0x55,0xaa,0x13]:
  for command in range(256):
   for mode in [0,3]:
    for selector in [0,1,2,3,4,5,255]:
     m=bytearray(rng.randbytes(0x4000));frame=bytearray(rng.randbytes(32));frame[0]=header;frame[2]=command;frame[4]=selector
     m[0x2000:0x2020]=frame;put16(m,0x878,mode)
     compare('dispatcher',0x0800b0dc,'recovered_dispatch_command',m,[R+0x2000],[header,command,mode,selector])
 for i in range(2500):
  m=bytearray(rng.randbytes(0x4000));ident=rng.getrandbits(32);amount=rng.choice([0,1,10,123,4999,5000,5001,0xaa33]);pending=rng.randrange(1,4000);old=rng.choice([ident,ident^1,0]);mode=rng.choice([0x55,0x66,0]);stage=rng.randrange(7)
  for off in [0x8be,0x8e0,0x8dc,0x12a,0x128,0x8d6,0x8da]:put16(m,off,0)
  put16(m,0x8be,1);put16(m,0x128,rng.choice([0,1]));m[0x854]=stage;put16(m,0x878,rng.randrange(4));put16(m,0x86e,rng.randrange(2));m[0x991]=rng.randrange(13);m[0x990]=rng.randrange(13)
  m[0x1018]=mode;put16(m,0x1020,pending);put32(m,0x101c,old);m[0x1022]=rng.randrange(25)
  old_amount=rng.choice([rng.randrange(65536),(pending+amount)&65535,(amount-pending)&65535]);put16(m,0x101a,old_amount)
  m[0x1024:0x102c]=bytes([0x55,0xaa])+ident.to_bytes(4,'big')+amount.to_bytes(2,'big')
  compare('identifier',0x08009694,'recovered_handle_identifier_frame',m,[],[i,amount,pending,old_amount,mode,stage])
 # Targeted record matching, history matching, request and confirmation branches.
 for scenario in range(180):
  m=bytearray(rng.randbytes(0x4000)); ident=0x12345679;pending=100;amount=[0,100,1234,0xaa33][scenario%4]
  for off in [0x8be,0x8e0,0x8dc,0x12a,0x128,0x8d6,0x8da]:put16(m,off,0)
  put16(m,0x8be,1);m[0x854]=[1,2,3,4,5][scenario%5];m[0x855]=255
  put16(m,0x878,scenario%4);put16(m,0x86e,1);put16(m,0x884,0);put16(m,0x882,0)
  m[0x991]=[0,3,12][scenario%3];m[0x990]=11;m[0x1022]=scenario%12
  m[0x1018]=[0x55,0x66][scenario%2];put16(m,0x1020,pending);put32(m,0x101c,ident)
  put16(m,0x101a,(pending+amount if scenario%2==0 else amount-pending)&65535)
  m[0x1024:0x102c]=bytes([0x55,0xaa])+ident.to_bytes(4,'big')+amount.to_bytes(2,'big')
  put32(m,0x604,ident);put16(m,0x5f2,400);put32(m,0x9ac+12,ident);put16(m,0x992+6,300)
  if scenario%6==0:put32(m,0x101c,0)
  if scenario%6==1:put16(m,0x128,1)
  if scenario%6==2:put16(m,0x12a,100)
  if scenario%6==3:put16(m,0x8da,1)
  if scenario%6==4:put16(m,0x8c8,1);m[0xbe]=0
  compare('identifier',0x08009694,'recovered_handle_identifier_frame',m,[],['targeted',scenario])
 # Directed exceptional/saturation and formatting paths.
 for scenario in range(96):
  m=bytearray(0x4000);ident=0x12345679;pending=100;amount=[0,10,1010,1030,1000,2001,4000,0xaa33][scenario%8]
  mode=[0x55,0x66][scenario%2]
  put16(m,0x8be,1);put16(m,0x858,3);put16(m,0x85a,50);put16(m,0x87e,100)
  put16(m,0x128,1);put16(m,0x878,0);m[0x854]=1;m[0x855]=255;m[0x991]=0;m[0x990]=0
  m[0x1018]=mode;put16(m,0x1020,pending);put32(m,0x101c,ident);m[0x1022]=0
  put16(m,0x101a,(pending+amount if mode==0x55 else amount-pending)&65535)
  put32(m,0x890,0);put32(m,0x89c,ident);put16(m,0x8da,1)
  m[0x1024:0x102c]=bytes([0x55,0xaa])+ident.to_bytes(4,'big')+amount.to_bytes(2,'big')
  if scenario//8==1: put16(m,0x128,0);put32(m,0x101c,0);put32(m,0x9ac+12,ident);put16(m,0x992+6,300)
  if scenario//8==2: put16(m,0x128,0);put32(m,0x101c,0);put16(m,0x878,3);put16(m,0x8c8,1);put16(m,0x8d6,3)
  if scenario//8==3: put16(m,0x1020,0);put16(m,0x101a,amount)
  if scenario//8==4: m[0x991]=12
  if scenario//8==5: put16(m,0x8da,0);put32(m,0x89c,ident)
  if scenario//8==6: put16(m,0x128,0);put32(m,0x101c,0);put16(m,0x878,3);put16(m,0x8c8,1);put16(m,0x8d6,3);m[0x854]=4
  compare('identifier',0x08009694,'recovered_handle_identifier_frame',m,[],['directed',scenario])
 m=bytearray(0x4000);put16(m,0x8be,1);put16(m,0x128,1);m[0x854]=1
 m[0x1018]=0x66;put16(m,0x1020,1);put32(m,0x101c,0x12345679);put16(m,0x101a,0)
 m[0x1024:0x102c]=bytes.fromhex('55aa123456790001')
 compare('identifier',0x08009694,'recovered_handle_identifier_frame',m,[],['low-value-refund'])
 inventory=json.loads((ROOT/'recovery/full_assembly/instructions.json').read_text())
 coverage={}
 for name,lo,hi in [('dispatcher',0x0800b0dc,0x0800b6b2),('identifier',0x08009694,0x08009ce4)]:
  addresses={int(r['address'],16) for r in inventory if lo<=int(r['address'],16)<hi}
  hits=addresses&orig.visited
  coverage[name]={'static_instructions':len(addresses),'visited_instructions':len(hits),'not_visited':[hex(a) for a in sorted(addresses-hits)]}
 result={'result':'PASS' if not fails else 'FAIL','cases':counts,'instruction_coverage':coverage,'failures':fails,'source_sha256':hashlib.sha256(SRC.read_bytes()).hexdigest(),'firmware_sha256':hashlib.sha256(FW).hexdigest(),'limitations':['Opaque external callees have deterministic scripted return values/effects; this validates dispatcher/handler behavior under those stubs only.','Peripheral and full firmware execution are not verified.','Incoming dispatcher stack payload is supplied explicitly for invalid selectors.']}
 report_path('verification/business_result.json').write_text(json.dumps(result,indent=2)+'\n');print(json.dumps(result,indent=2))
