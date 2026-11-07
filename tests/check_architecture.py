#!/usr/bin/env python3
"""Enforce the useful boundary: reusable code cannot know MCU addresses/ABI."""
import hashlib
from pathlib import Path
import re

if not __debug__:
    raise RuntimeError("Run verification without Python optimization (-O)")

ROOT = Path(__file__).resolve().parents[1]
assert hashlib.sha256((ROOT / 'stm32_fw.hex').read_bytes()).hexdigest() == '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'
paths = list((ROOT / 'firmware/src').rglob('*.c')) + list((ROOT / 'firmware/include').rglob('*.h'))
assert paths
for path in paths:
    # Ignore explanatory comments; check executable dependencies/literals.
    source = re.sub(r'/\*.*?\*/|//[^\n]*', '', path.read_text(), flags=re.S)
    assert not re.search(r'\b0x(?:0800|2000|400[0-9a-f]|4800)[0-9a-f]{4}\b', source, re.I), path
    assert not re.search(r'\b(?:fw_|f_)080[0-9a-f]+|\b__asm\b', source), path
    assert not re.search(r'#\s*include.*(?:recovery|platform|\.c[">])', source), path
    assert not re.search(r'\b(?:malloc|calloc|realloc|free)\s*\(', source), path
    if '/domain/' in str(path):
        assert not re.search(r'#\s*include.*charge/(?:storage|protocol)\.h', source), path
print(f'PASS: {len(paths)} portable sources/headers; no MMIO, legacy ABI, heap or platform dependencies; original HEX intact')
