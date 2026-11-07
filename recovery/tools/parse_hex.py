#!/usr/bin/env python3
"""Strict Intel HEX inventory. Does not execute firmware or modify the input."""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import re
import struct


def parse_hex(path):
    raw = path.read_bytes()
    text = raw.decode('ascii')
    memory, counts, starts = {}, collections.Counter(), []
    base = 0
    eof = False
    duplicates = 0
    for line_no, line in enumerate(text.splitlines(), 1):
        if not line or not re.fullmatch(r':[0-9A-Fa-f]+', line):
            raise ValueError(f'line {line_no}: invalid record syntax')
        if eof:
            raise ValueError(f'line {line_no}: record after EOF')
        try:
            rec = bytes.fromhex(line[1:])
        except ValueError as exc:
            raise ValueError(f'line {line_no}: invalid hex') from exc
        if len(rec) < 5 or len(rec) != rec[0] + 5:
            raise ValueError(f'line {line_no}: byte count mismatch')
        if sum(rec) & 255:
            raise ValueError(f'line {line_no}: checksum mismatch')
        n, addr, kind, data = rec[0], int.from_bytes(rec[1:3], 'big'), rec[3], rec[4:-1]
        counts[kind] += 1
        if kind == 0:
            if addr + n > 0x10000:
                raise ValueError(f'line {line_no}: record crosses 16-bit address boundary')
            for i, b in enumerate(data):
                absolute = base + addr + i
                if absolute > 0xffffffff:
                    raise ValueError(f'line {line_no}: address overflow')
                if absolute in memory:
                    if memory[absolute] != b:
                        raise ValueError(f'line {line_no}: conflicting byte at {absolute:#x}')
                    duplicates += 1
                memory[absolute] = b
        elif kind == 1:
            if n != 0 or addr:
                raise ValueError(f'line {line_no}: invalid EOF')
            eof = True
        elif kind in (2, 4):
            if n != 2 or addr:
                raise ValueError(f'line {line_no}: invalid extended-address record')
            base = int.from_bytes(data, 'big') << (4 if kind == 2 else 16)
        elif kind in (3, 5):
            if n != 4 or addr:
                raise ValueError(f'line {line_no}: invalid start-address record')
            starts.append({'type': kind, 'data_hex': data.hex()})
        else:
            raise ValueError(f'line {line_no}: unsupported record type {kind}')
    if not eof or not memory:
        raise ValueError('missing EOF or empty image')
    keys = sorted(memory)
    ranges = []
    begin = previous = keys[0]
    for address in keys[1:]:
        if address != previous + 1:
            ranges.append((begin, previous + 1))
            begin = address
        previous = address
    ranges.append((begin, previous + 1))
    return raw, memory, ranges, dict(counts), starts, duplicates


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('input', type=Path, nargs='?', default=Path('stm32_fw.hex'))
    ap.add_argument('--output', type=Path, default=Path('recovery/artifacts'))
    ap.add_argument('--vector-count', type=int, default=45,
                    help='Analyst-selected count; default 45 established for this image by code at +0xB4')
    ap.add_argument('--vector-bases', default='0x08000000,0x08004000',
                    help='Comma-separated analyst-selected vector table addresses')
    args = ap.parse_args()
    raw, memory, spans, counts, starts, duplicates = parse_hex(args.input)
    begin, end = min(memory), max(memory) + 1
    if end - begin > 128 * 1024 * 1024:
        raise ValueError('refusing a flat image larger than 128 MiB')
    binary = bytes(memory.get(a, 255) for a in range(begin, end))
    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / 'firmware.bin').write_bytes(binary)
    non_ff_runs = []
    for match in re.finditer(b'[^\xff]+', binary):
        non_ff_runs.append({'start': f'0x{begin + match.start():08X}',
                            'end_exclusive': f'0x{begin + match.end():08X}',
                            'size': match.end() - match.start()})
    ff_runs = [{'start': f'0x{begin + m.start():08X}', 'end_exclusive': f'0x{begin + m.end():08X}',
                'size': m.end() - m.start()} for m in re.finditer(b'\xff{32,}', binary)]
    core_names = ['Initial_SP', 'Reset', 'NMI', 'HardFault', 'Reserved4', 'Reserved5',
                  'Reserved6', 'Reserved7', 'Reserved8', 'Reserved9', 'Reserved10',
                  'SVCall', 'Reserved12', 'Reserved13', 'PendSV', 'SysTick']
    irq_names = ['WWDG', 'Reserved', 'RTC', 'FLASH', 'RCC', 'EXTI0_1', 'EXTI2_3',
                 'EXTI4_15', 'Reserved', 'DMA1_Channel1', 'DMA1_Channel2_3',
                 'DMA1_Channel4_5', 'ADC1', 'TIM1_BRK_UP_TRG_COM', 'TIM1_CC',
                 'Reserved', 'TIM3', 'TIM6', 'Reserved', 'TIM14', 'TIM15',
                 'TIM16', 'TIM17', 'I2C1', 'I2C2', 'SPI1', 'SPI2', 'USART1', 'USART2']
    vector_bases = [int(v, 0) for v in args.vector_bases.split(',')]
    vectors = []
    vector_tables = []
    for vector_base in vector_bases:
        offset = vector_base - begin
        if offset < 0 or offset + args.vector_count * 4 > len(binary):
            raise ValueError('vector table outside image')
        table = []
        for i in range(args.vector_count):
            value = struct.unpack_from('<I', binary, offset + i * 4)[0]
            target = value & ~1
            table.append({'table_base': f'0x{vector_base:08X}', 'index': i,
                          'irqn': i - 16 if i >= 16 else '',
                          'name': core_names[i] if i < 16 else f'IRQ{i - 16}',
                          'stm32f030x8_candidate_name': core_names[i] if i < 16 else irq_names[i-16] if i-16 < len(irq_names) else '',
                          'slot_address': f'0x{vector_base+i*4:08X}', 'raw_value': f'0x{value:08X}',
                          'target_address': f'0x{target:08X}' if i and value else '',
                          'thumb': bool(value & 1) if i else '',
                          'target_in_image': begin <= target < end if i else ''})
        vectors.extend(table)
        vector_tables.append({'base': f'0x{vector_base:08X}', 'count': args.vector_count,
                              'initial_sp': table[0]['raw_value'], 'reset_vector': table[1]['raw_value']})
    with (args.output / 'vectors.csv').open('w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=list(vectors[0]))
        writer.writeheader()
        writer.writerows(vectors)
    strings = []
    for m in re.finditer(rb'[\x20-\x7e]{4,}', binary):
        strings.append(f'0x{begin+m.start():08X}\tASCII\t{m.group().decode("ascii")}')
    for m in re.finditer(rb'(?:[\x20-\x7e]\x00){4,}', binary):
        strings.append(f'0x{begin+m.start():08X}\tUTF16LE\t{m.group().decode("utf-16le")}')
    (args.output / 'strings.txt').write_text('\n'.join(sorted(strings)) + '\n')
    manifest = {
        'source_file': str(args.input), 'source_size_bytes': len(raw),
        'source_sha256': hashlib.sha256(raw).hexdigest(),
        'binary_sha256': hashlib.sha256(binary).hexdigest(),
        'validation': {'all_checksums_valid': True, 'eof_present': True,
                       'record_types': counts, 'identical_duplicate_bytes': duplicates},
        'image_base': f'0x{begin:08X}', 'image_end_exclusive': f'0x{end:08X}',
        'binary_size_bytes': len(binary), 'explicit_bytes': len(memory),
        'gap_fill_bytes': len(binary) - len(memory), 'gap_fill_value': '0xFF',
        'address_spans': [{'start': f'0x{a:08X}', 'end_exclusive': f'0x{b:08X}', 'size': b-a} for a,b in spans],
        'start_address_records': starts,
        'last_non_ff_address': f'0x{begin+len(binary.rstrip(bytes([255])))-1:08X}',
        'long_ff_runs': ff_runs, 'string_candidates': len(strings),
        'vector_count': args.vector_count,
        'vector_count_basis': 'Analyst-selected from the first Thumb code at 0x080000B4; not inferred by Intel HEX',
        'initial_sp': vectors[0]['raw_value'], 'reset_vector': vectors[1]['raw_value'],
        'vector_tables': vector_tables,
        'limitations': ['String candidates can be accidental instruction bytes.',
                        'Intel HEX has no original function/variable names, types, or source paths.',
                        'FF bytes are explicitly present here; semantic usage is not established by byte value.']
    }
    (args.output / 'manifest.json').write_text(json.dumps(manifest, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps(manifest, indent=2, ensure_ascii=False))


if __name__ == '__main__':
    main()
