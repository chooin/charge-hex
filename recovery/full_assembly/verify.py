#!/usr/bin/env python3
"""Independently compare the rebuilt Flash bytes with the original Intel HEX."""
import hashlib
import json
from pathlib import Path
import sys
import shutil
import subprocess
import tempfile

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT/'recovery/tools'))
from parse_hex import parse_hex
from reporting import report_path

# Use the existing strict decoder but do not rely on exported firmware.bin.
parsed=parse_hex(ROOT/'stm32_fw.hex')
memory=parsed[1]
actual=(HERE/'build/firmware.bin').read_bytes()
expected=bytes(memory[a] for a in range(0x08000000,0x08010000))
assert actual==expected, 'Rebuilt bytes differ from original HEX'
# Demonstrate that build inputs consist only of human-readable assembly,
# linker script and Makefile, without the original BIN/HEX or generator.
with tempfile.TemporaryDirectory(prefix='firmware-source-only-build-') as folder:
    temporary=Path(folder)
    for name in ('firmware.S','firmware.ld','Makefile'):
        shutil.copyfile(HERE/name,temporary/name)
    subprocess.run(['make','-C',str(temporary),'all'],check=True,capture_output=True,text=True)
    assert (temporary/'build/firmware.bin').read_bytes()==expected, 'Source-only rebuild differs'
report={'result':'PASS','bytes':len(actual),'sha256':hashlib.sha256(actual).hexdigest(),
        'source':'original Intel HEX decoded with checksum validation','hardware_execution':False,
        'standalone_build_inputs':['firmware.S','firmware.ld','Makefile'],
        'standalone_build_without_input_binary':True,
        'source_sha256':hashlib.sha256((HERE/'firmware.S').read_bytes()).hexdigest()}
report_path('full_assembly/roundtrip_result.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
