#!/usr/bin/env python3
"""Reconstruct an address-preserving GNU Thumb assembly view of this firmware.

The classifier is conservative recursive control-flow discovery, not a claim
that every remaining byte is data. Known literal pools and Keil switch8 tables
are excluded from code. Bytes outside discovered instructions are explicit data.
The output has no .incbin and never depends on the input at assembly/link time.
"""
from __future__ import annotations
import argparse
from collections import Counter, deque
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import tempfile

from capstone import Cs, CS_ARCH_ARM, CS_MODE_THUMB, CS_MODE_MCLASS, CS_GRP_JUMP, CS_GRP_CALL
from capstone.arm_const import ARM_OP_IMM, ARM_OP_REG, ARM_OP_MEM, ARM_REG_PC, ARM_REG_LR

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
BASE = 0x08000000
END = BASE + 0x10000
CODE_RANGES = [(BASE + 0xB4, BASE + 0x2EF4), (BASE + 0x40B4, BASE + 0xCE78)]
NORETURN = {BASE+0xBC, BASE+0x40BC, BASE+0x2CF4, BASE+0xA708}
SWITCH8 = BASE + 0x95D2
# Additional instruction boundaries established by manual gap audit. These
# branches/stubs have no observed incoming edge; do not invent callable roots.
AUDITED_UNUSED_INSTRUCTIONS = {
    0x0CDC:'ffe7', 0x1970:'05e0', 0x1CA8:'ffe7', 0x2414:'ffe7',
    0x5FA8:'ffe7', 0x6FAC:'05e0', 0x7BB0:'02e0', 0xB2EC:'ffe7',
    0x2CE2:'7047', 0x963E:'7047',
}
AUDITED_DATA = [
    (0x02EC,8,'app.bin-string; ADR/read at 08000282/84'),
    (0x1368,32,'PLL-lookup-table; ADR/LDM at 08001316/18 and 08001320/22'),
    (0x666C,32,'PLL-lookup-table; application counterpart of boot table'),
    (0x2EBC,24,'AHB/APB-shift-tables; indexed LDRB at 080012CC and 08001302'),
    (0xCE60,24,'AHB/APB-shift-tables; application counterpart of boot tables'),
]
KNOWN_ENTRIES = {
    BASE+0xB4: 'boot_runtime_entry', BASE+0xC8: 'boot_Reset_Handler',
    BASE+0x2CF4: 'boot_main', BASE+0x40B4: 'app_runtime_entry',
    BASE+0x40CC: 'app_Reset_Handler', BASE+0xA708: 'app_main',
    BASE+0x2CD4: 'boot_scatter_copy', BASE+0x2CE4: 'boot_scatter_zero',
    BASE+0x9630: 'app_scatter_copy', BASE+0x9640: 'app_scatter_zero',
    BASE+0x1A4: 'boot_unreferenced_runtime_wrapper',
    BASE+0x41D0: 'app_unreferenced_runtime_wrapper',
}


class Discovery:
    def __init__(self, image: bytes):
        self.image = image
        self.cs = Cs(CS_ARCH_ARM, CS_MODE_THUMB | CS_MODE_MCLASS)
        self.cs.detail = True
        self.code = {}
        self.occupied = {}
        self.data = {}  # byte -> classification
        self.pool_words = set()
        self.tables = []
        self.seed_reasons = {}
        self.targets = set()
        self.pending = deque()
        self.issues = []
        self.indirect = {}
        self.functions = set()
        self.rejected = []

    def inside_code(self, address):
        return address % 2 == 0 and any(lo <= address < hi for lo, hi in CODE_RANGES)

    def word(self, address):
        return struct.unpack_from('<I', self.image, address - BASE)[0]

    def seed(self, address, reason, function=False):
        address &= ~1
        if not self.inside_code(address):
            return
        self.seed_reasons.setdefault(address, set()).add(reason)
        if function:
            self.functions.add(address)
        self.targets.add(address)
        self.pending.append(address)

    def mark_data(self, address, count, kind):
        if not BASE <= address <= END-count:
            return
        for p in range(address, address+count):
            if p in self.occupied:
                self.issues.append({'kind': 'code-data-overlap', 'address': hex(p),
                                    'data_kind': kind, 'instruction': hex(self.occupied[p])})
            self.data[p] = kind

    def discover(self):
        for offset,count,kind in AUDITED_DATA:
            self.mark_data(BASE+offset,count,kind)
        for table in (BASE, BASE+0x4000):
            self.mark_data(table, 45*4, 'vector-table')
            for i in range(1, 45):
                pointer = self.word(table + 4*i)
                if pointer & 1:
                    self.seed(pointer, f'vector:{table:#x}:{i}', True)
        for address in KNOWN_ENTRIES:
            self.seed(address, 'manually-established-entry', True)
        for offset,expected in AUDITED_UNUSED_INSTRUCTIONS.items():
            assert self.image[offset:offset+2].hex()==expected
            self.seed(BASE+offset,'manually-audited-unreferenced-instruction')
        for offset in (0xD0,0xD2,0xD4,0xD6,0xD8,0x40D4,0x40D6,0x40D8,0x40DA,0x40DC):
            self.seed(BASE+offset, 'adjacent-unreferenced-default-handler-self-loop', True)
        # The original scatter table names these functions by even addresses.
        for table in (BASE+0x2ED4, BASE+0xCE78):
            self.mark_data(table, 32, 'scatter-descriptors')
            for offset in (12, 28):
                self.seed(self.word(table+offset), 'scatter-function-pointer', True)
        self.drain()
        # Seed in-image Thumb function pointers stored in already identified
        # pools/vectors and non-code words, after the first pass has excluded
        # instruction encodings. This is explicitly an analyst heuristic.
        pointer_candidates = []
        for address in range(BASE, BASE+0xCF28, 4):
            if any(address+i in self.occupied for i in range(4)):
                continue
            pointer = self.word(address)
            target = pointer & ~1
            if pointer & 1 and self.inside_code(target) and target not in self.data:
                ins = next(self.cs.disasm(self.image[target-BASE:target-BASE+4], target, count=1), None)
                # Only common function starts, avoiding arbitrary flash string
                # pointers. Other computed targets remain unresolved.
                if ins and ins.mnemonic in ('push', 'ldr', 'bx', 'movs', 'b'):
                    pointer_candidates.append((address, target))
        for address, target in pointer_candidates:
            self.seed(target, f'pointer-word-heuristic:{address:#x}', True)
        self.drain()
        return self

    def drain(self):
        while self.pending:
            address = self.pending.popleft()
            constants = {}
            while self.inside_code(address):
                if address in self.code or address in self.data:
                    break
                if address in self.occupied:
                    self.issues.append({'kind': 'target-inside-instruction', 'address': hex(address),
                                        'owner': hex(self.occupied[address])})
                    break
                instruction = next(self.cs.disasm(self.image[address-BASE:address-BASE+4], address, count=1), None)
                if instruction is None:
                    self.rejected.append({'address': hex(address), 'reason': 'no Thumb decode'})
                    break
                # This target uses ARMv6-M. Capstone sometimes accepts later-ISA
                # encodings when a bad target lands on data; reject those here.
                if instruction.size == 4 and instruction.mnemonic not in ('bl', 'mrs', 'msr', 'dmb', 'dsb', 'isb'):
                    self.rejected.append({'address': hex(address), 'reason': 'not supported ARMv6-M encoding',
                                          'decode': instruction.mnemonic+' '+instruction.op_str})
                    break
                if any(address+i in self.data or address+i in self.occupied for i in range(instruction.size)):
                    break
                self.code[address] = instruction
                for p in range(address, address+instruction.size):
                    self.occupied[p] = address
                ops = instruction.operands
                mnemonic = instruction.mnemonic
                previous = dict(constants)
                for reg in instruction.regs_access()[1]:
                    constants.pop(reg, None)
                if mnemonic == 'ldr' and len(ops) == 2 and ops[1].type == ARM_OP_MEM and ops[1].mem.base == ARM_REG_PC:
                    literal = ((address+4)&~3) + ops[1].mem.disp
                    self.targets.add(literal)
                    self.pool_words.add(literal)
                    self.mark_data(literal, 4, 'literal-pool')
                    if BASE <= literal <= END-4:
                        constants[ops[0].reg] = self.word(literal)
                elif mnemonic in ('mov', 'movs') and len(ops) == 2:
                    if ops[1].type == ARM_OP_IMM:
                        constants[ops[0].reg] = ops[1].imm & 0xFFFFFFFF
                    elif ops[1].type == ARM_OP_REG and ops[1].reg in previous:
                        constants[ops[0].reg] = previous[ops[1].reg]

                immediate_branch = ((instruction.group(CS_GRP_JUMP) or instruction.group(CS_GRP_CALL))
                                    and ops and ops[0].type == ARM_OP_IMM)
                if immediate_branch:
                    target = ops[0].imm & ~1
                    call = instruction.group(CS_GRP_CALL)
                    self.seed(target, f'{mnemonic}:{address:#x}', bool(call))
                    if mnemonic == 'bl' and target == SWITCH8:
                        start = address + instruction.size
                        count = self.image[start-BASE]
                        size = count+2
                        self.mark_data(start, size, 'switch8-table')
                        targets = []
                        for index in range(count+1):
                            displacement = self.image[start-BASE+1+index]
                            destination = (start + 1 + 2*displacement) & ~1
                            targets.append(destination)
                            self.seed(destination, f'switch8:{address:#x}:case{index}')
                        self.tables.append({'call': hex(address), 'helper': hex(target), 'start': hex(start),
                                            'bytes': size, 'case_count': count, 'default_index': count,
                                            'targets': [hex(x) for x in targets]})
                        break
                    if mnemonic in ('b', 'b.w') or target in NORETURN:
                        break
                    if call:
                        constants = {}
                elif mnemonic in ('bx', 'blx'):
                    reg = ops[0].reg
                    value = previous.get(reg)
                    if value is not None:
                        self.seed(value, f'resolved-{mnemonic}:{address:#x}', mnemonic == 'blx')
                    elif not (mnemonic == 'bx' and reg == ARM_REG_LR):
                        self.indirect[address] = mnemonic+' '+instruction.op_str
                    if mnemonic == 'bx':
                        break
                    constants = {}
                elif mnemonic == 'pop' and any(o.type == ARM_OP_REG and o.reg == ARM_REG_PC for o in ops):
                    break
                elif mnemonic == 'mov' and ops and ops[0].type == ARM_OP_REG and ops[0].reg == ARM_REG_PC:
                    self.indirect[address] = mnemonic+' '+instruction.op_str
                    break
                elif mnemonic in ('udf',):
                    break
                address += instruction.size


def label(address):
    return f'.L_{address:08x}'


def source_for_instruction(ins):
    text = ins.mnemonic + (' '+ins.op_str if ins.op_str else '')
    if ((ins.group(CS_GRP_JUMP) or ins.group(CS_GRP_CALL)) and ins.operands
            and ins.operands[0].type == ARM_OP_IMM):
        target = ins.operands[0].imm & ~1
        mnemonic = ins.mnemonic
        if ins.size == 2:
            mnemonic += '.n'
        return f'{mnemonic} {label(target)}'
    if ins.mnemonic == 'ldr' and len(ins.operands) == 2 and ins.operands[1].type == ARM_OP_MEM and ins.operands[1].mem.base == ARM_REG_PC:
        target = ((ins.address+4)&~3) + ins.operands[1].mem.disp
        return f'ldr {ins.reg_name(ins.operands[0].reg)}, {label(target)}'
    if ins.mnemonic == 'adr':
        # Thumb ADR T1 immediate is an offset from aligned PC, not an address.
        halfword = int.from_bytes(ins.bytes[:2], 'little')
        target = ((ins.address+4)&~3) + (halfword&255)*4
        return f'adr {ins.reg_name(ins.operands[0].reg)}, {label(target)}'
    return text


def emit(discovery, destination, fallback):
    targets = set(discovery.targets)
    for address, ins in discovery.code.items():
        if ins.mnemonic == 'adr':
            targets.add(((address+4)&~3)+(int.from_bytes(ins.bytes[:2],'little')&255)*4)
    lines = ['/* Reconstructed from stm32_fw.hex. Not original source. */',
             '/* Instruction classification: see coverage.json; unknown bytes are preserved as data. */',
             '.syntax unified', '.cpu cortex-m0plus', '.thumb', '.section .firmware,"ax",%progbits',
             '.global firmware_image_start', 'firmware_image_start:']
    line_addresses = {}
    for address,name in KNOWN_ENTRIES.items():
        lines += [f'.global {name}', f'.thumb_set {name}, {label(address)}']
    for address in sorted(discovery.functions):
        if address in discovery.code:
            name=f'fw_{address:08x}'
            lines += [f'.global {name}', f'.thumb_set {name}, {label(address)}']
    for address in sorted(targets):
        if not BASE<=address<END:
            lines.append(f'.equ {label(address)}, 0x{address:08x}')
    address=BASE
    while address<END:
        if address in (BASE,BASE+0x4000,BASE+0xCF28,BASE+0xF800,BASE+0xFC00):
            descriptions={BASE:'BOOTLOADER PARTITION + VECTOR TABLE',BASE+0x4000:'APPLICATION PARTITION + VECTOR TABLE',
                          BASE+0xCF28:'EXPLICIT FF / TAIL DATA AREA',BASE+0xF800:'UPDATE METADATA PAGE',BASE+0xFC00:'CONFIGURATION PAGE'}
            lines.append('\n/* ===== '+descriptions[address]+' ===== */')
        ins=discovery.code.get(address)
        if ins:
            lines.append(label(address)+':')
            name=KNOWN_ENTRIES.get(address)
            if name:
                lines.append(f'    /* {name} */')
            text=source_for_instruction(ins)
            if address in fallback:
                if ins.size==2:
                    text=f'.inst.n 0x{int.from_bytes(ins.bytes,"little"):04x}'
                else:
                    value=(int.from_bytes(ins.bytes[:2],'little')<<16)|int.from_bytes(ins.bytes[2:],'little')
                    text=f'.inst.w 0x{value:08x}'
                text+=f' /* exact encoding: {ins.mnemonic} {ins.op_str}; {fallback[address]} */'
            lines.append(f'    {text:<48} /* {address:08x}: {ins.bytes.hex()} */')
            line_addresses[len(lines)]=address
            address+=ins.size
            continue
        if address in targets or address in (BASE,BASE+0x4000,BASE+0xF800,BASE+0xFC00):
            lines.append(label(address)+':')
        size=4 if address%4==0 and address+4<=END and not any(address+i in discovery.code or address+i in targets for i in range(1,4)) else 1
        value=int.from_bytes(discovery.image[address-BASE:address-BASE+size],'little')
        directive='.word' if size==4 else '.byte'
        kind=discovery.data.get(address, 'unclassified-data-or-code')
        if address>=BASE+0xCF28 and value==(1<<(size*8))-1:
            kind='explicit-FF-fill'
        lines.append(f'    {directive} 0x{value:0{size*2}x}'+f'  /* {address:08x}: {kind} */')
        address+=size
    lines += ['.global firmware_image_end', 'firmware_image_end:']
    destination.write_text('\n'.join(lines)+'\n')
    return line_addresses


def command(args):
    return subprocess.run(args, capture_output=True, text=True)


def build_and_verify(discovery):
    source=HERE/'firmware.S'
    build=HERE/'build'
    build.mkdir(exist_ok=True)
    fallback={}
    for attempt in range(10):
        locations=emit(discovery,source,fallback)
        assembled=command(['arm-none-eabi-as','-mcpu=cortex-m0plus','-mthumb',str(source),'-o',str(build/'firmware.o')])
        if assembled.returncode:
            changed=False
            for line in assembled.stderr.splitlines():
                match=re.search(r'firmware\.S:(\d+): Error: (.*)',line)
                if match and int(match[1]) in locations:
                    addr=locations[int(match[1])]
                    if addr not in fallback:
                        fallback[addr]='assembler alias rejected: '+match[2]
                        changed=True
            if changed:
                continue
            raise RuntimeError(assembled.stderr)
        linked=command(['arm-none-eabi-ld','-T',str(HERE/'firmware.ld'),str(build/'firmware.o'),'-o',str(build/'firmware.elf')])
        if linked.returncode:
            raise RuntimeError(linked.stderr)
        subprocess.run(['arm-none-eabi-objcopy','-O','binary',str(build/'firmware.elf'),str(build/'firmware.bin')],check=True)
        output=(build/'firmware.bin').read_bytes()
        if len(output)!=len(discovery.image):
            raise RuntimeError(f'Image size changed: {len(output)} != {len(discovery.image)}')
        differences=[BASE+i for i,(a,b) in enumerate(zip(output,discovery.image)) if a!=b]
        if not differences:
            subprocess.run(['arm-none-eabi-objcopy','-O','ihex',str(build/'firmware.elf'),str(build/'firmware.hex')],check=True)
            return output,fallback
        changed=False
        for address in differences:
            owner=discovery.occupied.get(address)
            if owner is None:
                raise RuntimeError(f'Non-instruction data changed at {address:#x}')
            if owner not in fallback:
                fallback[owner]='assembler selected a different equivalent encoding'
                changed=True
        if not changed:
            raise RuntimeError(f'Roundtrip differences remained: {differences[:10]}')
    raise RuntimeError('Too many assembly correction passes')


def main():
    image=(ROOT/'recovery/artifacts/firmware.bin').read_bytes()
    if len(image)!=0x10000:
        raise SystemExit('Expected the established 64-KiB image')
    discovery=Discovery(image).discover()
    output,fallback=build_and_verify(discovery)
    code_bytes=sum(i.size for i in discovery.code.values())
    unclassified=[]
    begin=None
    for address in range(BASE,END+1):
        unknown=address<END and any(lo<=address<hi for lo,hi in CODE_RANGES) and address not in discovery.occupied and address not in discovery.data
        if unknown and begin is None:
            begin=address
        elif not unknown and begin is not None:
            unclassified.append({'start':hex(begin),'end_exclusive':hex(address),'bytes':address-begin,
                                 'hex':image[begin-BASE:address-BASE].hex()})
            begin=None
    report={
        'image_sha256':hashlib.sha256(image).hexdigest(), 'rebuilt_sha256':hashlib.sha256(output).hexdigest(),
        'image_bytes':len(image), 'exact_flash_roundtrip':output==image,
        'instructions':len(discovery.code), 'classified_instruction_bytes':code_bytes,
        'mnemonic_instructions':len(discovery.code)-len(fallback), 'exact_encoding_fallbacks':len(fallback),
        'remaining_explicit_data_bytes':len(image)-code_bytes,
        'unclassified_bytes_within_code_ranges':sum(r['bytes'] for r in unclassified),
        'unclassified_ranges_within_code_ranges':unclassified,
        'literal_pool_words':len(discovery.pool_words), 'switch8_tables':discovery.tables,
        'seeded_function_entries':len(discovery.functions),
        'unresolved_indirect_branches':[{ 'address':hex(a),'instruction':s} for a,s in sorted(discovery.indirect.items())],
        'classification_conflicts':discovery.issues, 'rejected_decode_paths':discovery.rejected,
        'fallbacks':[{ 'address':hex(a),'reason':s} for a,s in sorted(fallback.items())],
        'limitations':[
            'A byte-identical rebuilt image proves preservation of bytes, not correctness of every code/data classification.',
            'Function seeds include vectors, known entries, direct calls and a bounded pointer-word heuristic; these are analyst names.',
            'Unclassified bytes may contain additional code. They are explicit data, not silently represented as recovered source functions.',
            'All original absolute addresses and instruction widths are retained; changing layout requires updating literal data and pointers.',
            'No hardware execution or flashing was performed.']}
    (HERE/'coverage.json').write_text(json.dumps(report,indent=2)+'\n')
    instructions=[{'address':f'{a:#010x}','size':i.size,'bytes':i.bytes.hex(),'mnemonic':i.mnemonic,'operands':i.op_str}
                  for a,i in sorted(discovery.code.items())]
    (HERE/'instructions.json').write_text(json.dumps(instructions,indent=2)+'\n')
    (HERE/'seeds.json').write_text(json.dumps([{'address':hex(a),'reasons':sorted(rs)} for a,rs in sorted(discovery.seed_reasons.items())],indent=2)+'\n')
    print(json.dumps({k:report[k] for k in ['exact_flash_roundtrip','image_bytes','instructions','classified_instruction_bytes','mnemonic_instructions','exact_encoding_fallbacks','literal_pool_words','seeded_function_entries']},indent=2))


if __name__=='__main__':
    main()
