#!/usr/bin/env python3
"""Evidence-led audit of the 509-byte gap inventory retained before refinement."""
from collections import Counter
import hashlib
import json
from pathlib import Path

HERE=Path(__file__).resolve().parent
baseline=json.loads((HERE/'gap_audit_baseline.json').read_text())
coverage=json.loads((HERE/'coverage.json').read_text())

tables={
  0x08001368:('PLL multiplier/predivider lookup arrays','08001316/18 ADR+LDM first16; 08001320/22 ADR+LDM second16; indexed byte use 08001340/4A'),
  0x0800666c:('PLL multiplier/predivider lookup arrays','app analogue of 08001368; ADR/LDM at 0800661A/1C and 08006624/26'),
  0x08002ebc:('AHB/APB prescaler shift lookup arrays','pointer words080012EC/08001310; indexed LDRB080012CC/08001302 followed by variable LSR'),
  0x0800ce60:('AHB/APB prescaler shift lookup arrays','pointer words080065F0/08006614; app analogue of08002EBC'),
}
rows=[]
parts=[]
for original in baseline['unclassified_ranges']:
    row=dict(original)
    address=int(row['start'],16)
    raw=bytes.fromhex(row['hex'])
    if address in tables:
        category='confirmed-constant-table'
        description,evidence=tables[address]
        confidence='direct-data-use'
        change='Classified as explicit data in generator; bytes unchanged.'
    elif address==0x080002ea:
        category='mixed-padding-and-string'
        description='2 zero alignment bytes, then app.bin NUL-terminated string (8 bytes)'
        evidence='08000282 ADR r1,080002EC; 08000284 LDM r1,{r0,r1}, then stored and passed to metadata write.'
        confidence='string-direct-data-use; alignment-inferred'
        change='8 string bytes classified as data; 2 leading zero bytes remain padding candidates.'
        parts += [('zero-padding-candidate',2),('confirmed-string',8)]
    elif raw==b'\0\0':
        category='zero-padding-candidate'
        description='One 0000 halfword between a terminal/basic-block end and an aligned pool/next function.'
        evidence='Not reached by discovered CFG; repeated word-alignment layout in boot/app; 0000 alone is also a valid MOVS alias.'
        confidence='inferred-padding; not-proof-of-unreachability'
        change='Kept explicit data; not relabeled as a source instruction merely to claim coverage.'
    elif raw==b'\0':
        category='switch-table-padding-candidate'
        description='Single zero byte after an odd-length switch8 table, before next aligned instruction.'
        evidence='End of compiler inline switch8 table at '+row['start']+'; next instruction begins at '+row['end_exclusive']+'.'
        confidence='structural-alignment-inference'
        change='Kept explicit data.'
    elif raw==bytes.fromhex('c046c046'):
        category='nop-padding-candidate'
        description='Two MOV r8,r8 (NOP) encodings between runtime branch target literal and initial stack literal.'
        evidence='080040BE BX r0 leaves startup fragment; main pointer at080040C0; SP literal at080040C8; no discovered incoming edge.'
        confidence='decoded-NOP; padding-role-inferred'
        change='Kept explicit data as nonexecuted alignment candidate, not promoted to a function.'
    elif raw in (bytes.fromhex('ffe7'),bytes.fromhex('05e0'),bytes.fromhex('02e0')):
        category='unreferenced-branch-instruction'
        offset=int.from_bytes(raw,'little')&0x7ff
        if offset&0x400:offset-=0x800
        destination=address+4+offset*2
        description=f'B.n {destination:#010x}; redundant branch/island within surrounding decoded function.'
        evidence='Exact Thumb branch encoding; destination is established code, adjacent instructions are compiler branch/return paths. No incoming CFG edge found.'
        confidence='instruction-encoding-certain; reachability-unobserved'
        change='Added to mnemonic assembly as manually audited unreferenced instruction.'
    elif raw==bytes.fromhex('7047'):
        category='unreferenced-return-stub'
        description='BX LR directly between scatter-copy and scatter-zero routines; candidate scatterload null helper.'
        evidence='Same isolated BX LR in boot08002CE2 and app0800963E. Current two scatter descriptors select copy/zero, not this stub.'
        confidence='instruction-encoding-certain; helper-name-inferred'
        change='Added BX LR mnemonic; not assigned an invented original function name.'
    else:
        category='unresolved'
        description='No established classification.'
        evidence='Bytes retained.'
        confidence='unknown'
        change='None.'
    if category!='mixed-padding-and-string':
        parts.append((category,len(raw)))
    row.update(category=category,description=description,evidence=evidence,confidence=confidence,action=change)
    rows.append(row)

indirect=[
 {'address':'0x080001E8','instruction':'BLX r3','role':'boot scatter-loading callback','resolution':'resolved-for-current-descriptors',
  'targets':['0x08002CD4','0x08002CE4'],'evidence':'R4 walks 16-byte descriptors08002ED4..08002EF4; word+12 OR1 selects copy/zero. Both targets already in source.'},
 {'address':'0x0800052E','instruction':'BLX r1','role':'DMA handle +0x34 callback; abort-completion role inferred','resolution':'partial-observed-registration',
  'targets':['0x0800266C'],'evidence':'0528 loads [r0+34] and null-checks. UART error path1942/1944 installs pointer0800266D from literal1A68 before DMA abort. Other dynamic handle values are not proved absent.'},
 {'address':'0x080005EE','instruction':'BX r1','role':'DMA handle +0x28 transfer-completion tail callback','resolution':'partial-observed-registration',
  'targets':['0x080026CC'],'evidence':'05E6 loads [r0+28], null-checks and tailcalls. UART RX DMA setup28DC/28DE installs080026CD from293C. Shared DMA handler can receive other handle callbacks.'},
 {'address':'0x08001914','instruction':'BLX r1','role':'UART handle +0x64 RX interrupt function pointer','resolution':'runtime-pointer; no-established-nonzero-target',
  'targets':[],'evidence':'1904..1910 gate on status/control bit5 and null-check [r4+64]. Initialization2898/289A and end-receive2770/2772 clear the field. DMA setup is observed; nonzero RxISR installation not established.'},
 {'address':'0x08001964','instruction':'BLX r1','role':'shared UART IRQ dispatch; DMA abort callback or RX function pointer','resolution':'partial-observed-registration',
  'targets':['0x0800266C'],'evidence':'1950/1952 path obtains [UART+70] DMA handle then callback+34, registered at1944. Other predecessors reach same call using UART+64. Single target is not exhaustive.'},
 {'address':'0x08002E46','instruction':'BLX r0','role':'Boot-to-application handoff','resolution':'resolved-for-current-flash-image',
  'targets':['0x080040CC'],'evidence':'2E44 loads saved App reset vector; current word at08004004=080040CD. Firmware updates may replace that vector; current target already seeded.'},
 {'address':'0x08004540','instruction':'BLX r3','role':'app scatter-loading callback','resolution':'resolved-for-current-descriptors',
  'targets':['0x08009630','0x08009640'],'evidence':'R4 walks descriptors0800CE78..0800CE98; +12 OR1 selects app copy/zero.'},
 {'address':'0x080058C6','instruction':'BLX r1','role':'DMA handle +0x34 callback; abort-completion role inferred','resolution':'partial-observed-registration',
  'targets':['0x080090B4'],'evidence':'58C0 loads [r0+34]. UART error6F7E/6F80 installs080090B5 from70A4 then calls abort5884.'},
 {'address':'0x08005938','instruction':'BX r1','role':'DMA handle +0x28 transfer-completion tail callback','resolution':'partial-observed-registration',
  'targets':['0x08009114','0x0800918C'],'evidence':'5930 loads [r0+28]. RX setup935C/935E registers08009115 from93BC; TX setup72D6 registers0800918D from7324. Other peripherals can use same DMA code.'},
 {'address':'0x08006F50','instruction':'BLX r1','role':'UART handle +0x64 RX interrupt function pointer','resolution':'runtime-pointer; no-established-nonzero-target',
  'targets':[],'evidence':'6F40..6F4C bit5 gates plus null-check.9318/931A and91F0/91F2 clear field. DMA operation observed; no nonzero target established by this audit.'},
 {'address':'0x08006FA0','instruction':'BLX r1','role':'shared UART IRQ dispatch; DMA abort callback or RX function pointer','resolution':'partial-observed-registration',
  'targets':['0x080090B4'],'evidence':'6F8C/6F8E load DMA handle+34 after registration6F80; other predecessors can use UART+64.'},
 {'address':'0x080095EA','instruction':'BX r3','role':'Keil switch8 table dispatcher','resolution':'resolved-per-eight-static-call-sites',
  'targets':sorted({x for table in coverage['switch8_tables'] for x in table['targets']},key=lambda x:int(x,16)),
  'evidence':'Uses LR-1 table header, chooses min(r3,count), base=(table+1), branch to(base+2*uint8_offset)&~1. Eight tables and all case/default destinations explicitly recorded in coverage.json.'},
]
counts=Counter()
for key,n in parts:counts[key]+=n
assert sum(counts.values())==509
assert coverage['unclassified_bytes_within_code_ranges']==369
assert coverage['exact_flash_roundtrip']
report={
 'baseline_elf_sha256':baseline['source_elf_sha256'],
 'current_elf_sha256':hashlib.sha256((HERE/'build/firmware.elf').read_bytes()).hexdigest(),
 'flash_sha256':coverage['image_sha256'],'flash_bytes_changed':False,
 'baseline_gap_bytes':sum(r['bytes'] for r in rows),'baseline_gap_ranges':len(rows),
 'category_bytes':dict(counts),'classified_additional_instruction_bytes':20,'classified_additional_constant_bytes':120,
 'remaining_padding_candidates_bytes':369,'remaining_unexplained_blocks':0,
 'statement':'All original gaps now have evidence-backed categories; padding role is inferred, not proven. No claim of runtime reachability completeness.',
 'gaps':rows,'indirect_branches':indirect,
 'already_recovered_before_baseline':[
  {'addresses':['080001A4..080001B5','080041D0..080041E1'],'role':'unreferenced ARM runtime wrappers','bytes':36},
  {'addresses':['080000D0..080000D9','080040D4..080040DD'],'role':'adjacent unreferenced default handler B self loops','bytes':20}],
 'limitations':['Byte identity does not prove source-level semantics or hardware behavior.',
               'Function-pointer candidate targets are not an exhaustive dynamic target proof.',
               '0000 decodes as an instruction but its use as padding is inferred from alignment and missing CFG edges.',
               'Observed address-like data pointers and indirect calls do not prove any path executed on the physical board.']}
(HERE/'gap_audit.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n')
md=['# 未分类字节与间接跳转审计','',
    '审计对象是上一版覆盖表中的 **199 段、509 字节**。没有把能够解码的任意数据直接当代码；逐段检查上下文、读取引用和编译器结构。',
    '', '| 分类 | 字节数 | 处理 |','|---|---:|---|']
for key,n in counts.items():md.append(f'| {key} | {n} | 见逐段证据 |')
md += ['', '本轮将20字节明确的未引用分支/返回stub改为助记符，将120字节由实际读取指令确认的表/字符串标记为数据。剩下369字节是零填充或NOP填充候选，**仍保留为数据，不声称已经证明全部运行时可达性**。没有发现尚未解释的大块业务代码。',
       '', '完整Flash依旧逐字节一致；ELF的代码/数据分类和符号布局发生变化，继续分析应使用最新ELF。',
       '', '- 原ELF：`'+report['baseline_elf_sha256']+'`', '- 新ELF：`'+report['current_elf_sha256']+'`',
       '- Flash：`'+report['flash_sha256']+'`',
       '', '## 原509字节的逐段结果','', '| 开始地址 | 长度 | 分类 | 证据/解释 |','|---|---:|---|---|']
for r in rows:md.append(f'| `{r["start"]}` | {r["bytes"]} | {r["category"]} | {r["description"]} {r["evidence"]} |')
md += ['', '## 12处间接调用/跳转','', '自动CFG无法携带完整RAM状态，所以保留“间接”并不表示目标代码一定缺失。以下区分当前静态表可完全解释的目标、已观察注册的候选，以及仍取决于运行时内存的字段。','',
       '| 调用地址 | 角色 | 目标/结论 | 证据 |','|---|---|---|---|']
for r in indirect:
    targets=', '.join(r['targets']) if len(r['targets'])<10 else f'{len(r["targets"])} unique destinations in coverage.json switch tables'
    md.append(f'| `{r["address"]}` {r["instruction"]} | {r["role"]} | {r["resolution"]}; {targets or "unknown nonzero target"} | {r["evidence"]} |')
md += ['', '之前已补入的未引用runtime wrappers：`080001A4..080001B5`、`080041D0..080041E1`；默认异常自循环：`080000D0..080000D9`、`080040D4..080040DD`。它们不再计入本轮509字节，避免重复统计。','',
       '复现：`python3 recovery/full_assembly/audit_gaps.py`。此脚本只写审计报告，不修改输入固件或汇编。']
(HERE/'gap_audit.md').write_text('\n'.join(md)+'\n')
print(json.dumps({k:report[k] for k in ['baseline_gap_bytes','category_bytes','classified_additional_instruction_bytes','remaining_padding_candidates_bytes','current_elf_sha256']},indent=2))
