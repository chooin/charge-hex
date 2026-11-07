#!/usr/bin/env python3
"""Emit an explicit C semantic lift of every statically reachable main instruction.
No firmware execution. This is a machine-state reference, not production C.
"""
from pathlib import Path
import hashlib,json
from collections import Counter
from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS, CS_GRP_JUMP
from capstone.arm import ARM_OP_IMM,ARM_OP_REG,ARM_OP_MEM
ROOT=Path(__file__).resolve().parents[1]
B=(ROOT/'artifacts/firmware.bin').read_bytes(); BASE=0x08000000
START,END=0x0800a708,0x0800b0c8
D=Cs(CS_ARCH_ARM,CS_MODE_THUMB|CS_MODE_MCLASS);D.detail=True
code={}; queue=[START];switches={}
while queue:
 a=queue.pop()
 if a in code or not START<=a<END:continue
 i=next(D.disasm(B[a-BASE:a-BASE+4],a,count=1));code[a]=i
 if i.mnemonic=='bl' and i.operands[0].imm==0x080095d2:
  p=a+i.size-BASE;n=B[p]
  dest=[(BASE+p+1+2*B[p+1+x])&~1 for x in range(n+1)]
  switches[a]={'table':BASE+p,'count':n,'destinations':dest}
  queue.extend(dest);continue
 if i.group(CS_GRP_JUMP) and i.operands[0].type==ARM_OP_IMM:
  queue.append(i.operands[0].imm)
  if i.mnemonic=='b':continue
 if i.mnemonic=='bl' and START<=i.operands[0].imm<END:
  queue.append(i.operands[0].imm);continue
 queue.append(a+i.size)

def reg(i,r):
 name=i.reg_name(r)
 if name in ['sp','lr','pc','ip','sb','sl','fp']:return {'sp':13,'lr':14,'pc':15,'ip':12,'sb':9,'sl':10,'fp':11}[name]
 assert name.startswith('r'),name
 return int(name[1:])
def val(i,o):
 if o.type==ARM_OP_IMM:return f'0x{o.imm&0xffffffff:x}u'
 if o.type==ARM_OP_REG:return f's->r[{reg(i,o.reg)}]'
 raise ValueError((i.mnemonic,i.op_str,o.type))
def mem(i,o):
 assert o.type==ARM_OP_MEM
 m=o.mem
 base=f'0x{(i.address+4)&~3:x}u' if i.reg_name(m.base)=='pc' else f's->r[{reg(i,m.base)}]'
 if m.index:base+=f' + s->r[{reg(i,m.index)}]'
 if m.disp:base+=f' + 0x{m.disp&0xffffffff:x}u'
 return '('+base+')'

header='''/* Explicit register-state ABI for the recovered application main.
 * This is an offline semantic reference, not an MCU executable replacement.
 * External calls must implement the complete CPU/memory effects that matter to
 * main, including r0-r3/r12/lr/APSR; no dummy success implementations exist.
 */
#ifndef RECOVERY_APPLICATION_MAIN_H
#define RECOVERY_APPLICATION_MAIN_H
#include <stdint.h>
#include <stddef.h>
struct AppMainState;
typedef int (*AppMainCall)(void *, uint32_t target, struct AppMainState *);
typedef uint32_t (*AppMainIoRead)(void *, uint32_t address, unsigned width);
typedef void (*AppMainIoWrite)(void *, uint32_t address, unsigned width, uint32_t value);
typedef struct AppMainState {
    uint32_t r[16];
    uint32_t apsr; /* NZCV in bits 31..28, other bits retained */
    uint32_t pc;
    uint32_t fault_address;
    int32_t fault;
    uint64_t main_instruction_count;
    uint8_t *flash; /* exactly 65536 bytes at 0x08000000 */
    uint8_t *sram;
    uint32_t sram_size;
    void *user;
    AppMainCall call;
    AppMainIoRead io_read;
    AppMainIoWrite io_write;
} AppMainState;
/* Set pc=0x0800A708 for initialization, or resume a previously yielded state.
 * 0 = instruction budget consumed, 1 = external call requested a yield,
 * -1 = unmapped memory/entry, -2 = required external-call callback absent.
 * The enclosing hardware, IRQ schedule, and callee implementations are caller
 * responsibilities. A callback returning nonzero yields AFTER the BL.
 */
int recovered_application_main_run(AppMainState *state, uint32_t budget);
#endif
'''
(ROOT/'reconstructed/application_main.h').write_text(header)
prefix='''/* Whole-control-flow C semantic recovery of 0x0800A708..0x0800B0C6.
 * Generated from verified Thumb operands by tools/lift_application_main.py.
 * Explicit register names and address labels are intentional; this is NOT the
 * lost original source or a production-ready high-level firmware main.
 * No opaque opcode interpreter, bytecode execution, or TODO branch bodies.
 * Literal pools and the Keil switch8 table are data, excluded from instructions.
 */
#include "application_main.h"
#define NZ 0xC0000000u
#define CV 0x30000000u
static uint32_t nz(AppMainState*s,uint32_t x){s->apsr=(s->apsr&~NZ)|(x&0x80000000u)|(x?0:0x40000000u);return x;}
static uint32_t add(AppMainState*s,uint32_t a,uint32_t b){uint32_t r=a+b;s->apsr=(s->apsr&~CV)|((uint64_t)a+b>0xffffffffu?0x20000000u:0)|((~(a^b)&(a^r)&0x80000000u)?0x10000000u:0);return nz(s,r);}
static uint32_t sub(AppMainState*s,uint32_t a,uint32_t b){uint32_t r=a-b;s->apsr=(s->apsr&~CV)|(a>=b?0x20000000u:0)|(((a^b)&(a^r)&0x80000000u)?0x10000000u:0);return nz(s,r);}
static uint32_t lsl(AppMainState*s,uint32_t a,unsigned n){uint32_t r;if(!n)return nz(s,a);s->apsr=(s->apsr&~0x20000000u)|((n<=32&&((a>>(32-n))&1u))?0x20000000u:0);r=n<32?a<<n:0;return nz(s,r);}
static uint32_t lsr(AppMainState*s,uint32_t a,unsigned n){uint32_t r;if(!n)return nz(s,a);s->apsr=(s->apsr&~0x20000000u)|((n<=32&&((a>>(n-1))&1u))?0x20000000u:0);r=n<32?a>>n:0;return nz(s,r);}
static uint32_t read_mem(AppMainState*s,uint32_t a,unsigned n){const uint8_t*p=0;uint32_t v=0;if(a>=0x08000000u&&a-0x08000000u<=0x10000u-n)p=s->flash+(a-0x08000000u);else if(a>=0x20000000u&&s->sram_size>=n&&a-0x20000000u<=s->sram_size-n)p=s->sram+(a-0x20000000u);else if(s->io_read)return s->io_read(s->user,a,n);else{s->fault=-1;s->fault_address=a;return 0;}for(unsigned i=0;i<n;i++)v|=(uint32_t)p[i]<<(8*i);return v;}
static void write_mem(AppMainState*s,uint32_t a,unsigned n,uint32_t v){uint8_t*p=0;if(a>=0x20000000u&&s->sram_size>=n&&a-0x20000000u<=s->sram_size-n)p=s->sram+(a-0x20000000u);else if(s->io_write){s->io_write(s->user,a,n,v);return;}else{s->fault=-1;s->fault_address=a;return;}for(unsigned i=0;i<n;i++)p[i]=(uint8_t)(v>>(8*i));}
#define STEP(a) do{s->pc=(a);s->r[15]=(a)+4u;if(s->fault)return s->fault;if(!budget--)return 0;++s->main_instruction_count;}while(0)
#define C ((s->apsr>>29)&1u)
#define Z ((s->apsr>>30)&1u)
int recovered_application_main_run(AppMainState *s,uint32_t budget)
{
    uint32_t temp;
    goto dispatch;
dispatch:
    switch(s->pc) {
'''
lines=[prefix]
for a in sorted(code):lines.append(f'    case 0x{a:08x}u: goto L_{a:08x};')
lines+=['    default: s->fault=-1;s->fault_address=s->pc;return -1;','    }']
conditions={'beq':'Z','bne':'!Z','bhs':'C','blo':'!C','bhi':'C&&!Z','bls':'!C||Z'}
phase={0xa708:'Startup: vector remap and peripheral initialization',0xa7d4:'Main loop entry: watchdog, time delta',0xa7fa:'Scan 93 software timer slots',0xa888:'Keil switch8 timer expiry dispatch',0xac64:'Global mode processing',0xacb8:'Twelve channel state updates',0xaf3a:'Poll and debounce inputs 1..15',0xb01a:'Consume both UART reception paths',0xb056:'Queued pulse-command output',0xb0a6:'Flush outputs, displays, input status, final processing'}
for a,i in sorted(code.items()):
 if a-BASE in phase:lines.append('\n    /* '+phase[a-BASE]+' */')
 lines.append(f'L_{a:08x}: STEP(0x{a:08x}u); /* {i.mnemonic} {i.op_str} */')
 o=i.operands;m=i.mnemonic;following=a+i.size
 st=[]
 if m in ('ldr','ldrh','ldrb'):st=[f'{val(i,o[0])}=read_mem(s,{mem(i,o[1])},{dict(ldr=4,ldrh=2,ldrb=1)[m]});']
 elif m in ('str','strh','strb'):st=[f'write_mem(s,{mem(i,o[1])},{dict(str=4,strh=2,strb=1)[m]},{val(i,o[0])});']
 elif m in ('mov','movs','uxtb','uxth','mvns'):
  x=val(i,o[1]);x={'uxtb':f'(uint8_t)({x})','uxth':f'(uint16_t)({x})','mvns':f'nz(s,~({x}))','movs':f'nz(s,{x})'}.get(m,x)
  st=[f'{val(i,o[0])}={x};']
 elif m in ('adds','subs','sub','lsls','lsrs','muls','orrs','ands','bics'):
  dst=val(i,o[0]);x=val(i,o[1]) if len(o)==3 else dst;y=val(i,o[2]) if len(o)==3 else val(i,o[1])
  # MULS R0,R1,R0 has the same commutative product; operands handled directly.
  expr={'adds':f'add(s,{x},{y})','subs':f'sub(s,{x},{y})','sub':f'({x})-({y})','lsls':f'lsl(s,{x},{y})','lsrs':f'lsr(s,{x},{y})','muls':f'nz(s,({x})*({y}))','orrs':f'nz(s,({x})|({y}))','ands':f'nz(s,({x})&({y}))','bics':f'nz(s,({x})&~({y}))'}[m]
  st=[f'{dst}={expr};']
 elif m in ('cmp','cmn'):st=[f'(void){"sub" if m=="cmp" else "add"}(s,{val(i,o[0])},{val(i,o[1])});']
 elif m=='b':st=[f'goto L_{o[0].imm:08x};'];following=None
 elif m in conditions:st=[f'if({conditions[m]})goto L_{o[0].imm:08x};']
 elif m=='bl':
  dest=o[0].imm;st=[f's->r[14]=0x{a+i.size+1:08x}u;']
  if dest==0x080095d2:
   sw=switches[a];t=sw['table'];count=sw['count']
   st += ['/* Inline exact switch8 helper; preserve its stack writes and NZCV. */',
    'write_mem(s,s->r[13]-8u,4,s->r[4]);write_mem(s,s->r[13]-4u,4,s->r[5]);',
    f'(void)sub(s,s->r[3],{count}u);temp=s->r[3]<{count}u?s->r[3]:{count}u;',
    f's->r[3]=read_mem(s,0x{t+1:08x}u+temp,1);',
    's->r[3]=lsl(s,s->r[3],1);',f's->r[3]=add(s,0x{t+1:08x}u,s->r[3]);',
    's->pc=s->r[3]&~1u;goto dispatch;'];following=None
  elif START<=dest<END:
   st.append(f'goto L_{dest:08x};');following=None
  else:
   st += [f'if(!s->call){{s->fault=-2;s->fault_address=0x{dest:08x}u;return -2;}}',
    f's->r[15]=0x{dest:08x}u;',f'temp=(uint32_t)s->call(s->user,0x{dest:08x}u,s);',
    f'if(temp){{s->pc=0x{following:08x}u;return 1;}}']
 else:raise ValueError((hex(a),m,i.op_str))
 lines+=['    '+x for x in st]
 if following is not None:
  assert following in code,(hex(a),hex(following))
  lines.append(f'    goto L_{following:08x};')
lines.append('}\n')
(ROOT/'reconstructed/application_main.c').write_text('\n'.join(lines))
report={'source_binary_sha256':hashlib.sha256(B).hexdigest(),'range_start':hex(START),'range_end_exclusive':hex(END),'instruction_count':len(code),'instruction_bytes':sum(i.size for i in code.values()),'mnemonics':dict(Counter(i.mnemonic for i in code.values())), 'external_calls':sorted(hex(i.operands[0].imm) for i in code.values() if i.mnemonic=='bl' and not START<=i.operands[0].imm<END and i.operands[0].imm!=0x80095d2),'switches':switches,'instructions':[{'address':hex(a),'size':i.size,'assembly':i.mnemonic+' '+i.op_str} for a,i in sorted(code.items())], 'limitations':['Static CFG discovery from actual main entry; code/data classification assumes the recognized switch8 helper semantics.','Complete control-flow semantic lift with machine-state ABI, not source-level types/names or complete callee implementation.']}
(ROOT/'artifacts/application_main_coverage.json').write_text(json.dumps(report,indent=2)+'\n')
print('generated',len(code),'main instructions')
