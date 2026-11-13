#!/usr/bin/env python3
"""Check original-image integrity and C syntax. No device access or flashing."""
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).parent))
from parse_hex import parse_hex
from reporting import report_path


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    original = ROOT / 'stm32_fw.hex'
    manifest = json.loads((ROOT / 'recovery/artifacts/manifest.json').read_text())
    assert sha(original.read_bytes()) == manifest['source_sha256'], 'Original HEX identity changed'
    # A separate GNU Intel HEX decoder cross-checks the Python parser output.
    parse_hex(original)
    binary = (ROOT / 'recovery/artifacts/firmware.bin').read_bytes()
    assert sha(binary) == manifest['binary_sha256']
    with tempfile.TemporaryDirectory(prefix='firmware-artifact-check-') as temp:
        temp = Path(temp)
        converted, elf_text = temp / 'converted.bin', temp / 'elf-text.bin'
        subprocess.run(['arm-none-eabi-objcopy', '-I', 'ihex', '-O', 'binary', str(original), str(converted)], check=True)
        subprocess.run(['arm-none-eabi-objcopy', '-O', 'binary', '-j', '.text', str(ROOT / 'recovery/artifacts/firmware.analysis.elf'), str(elf_text)], check=True)
        assert binary == converted.read_bytes(), 'Independent HEX decode differs'
        assert binary == elf_text.read_bytes(), 'Analysis ELF changed Flash bytes'
    files = sorted((ROOT / 'recovery/reconstructed').glob('*.c'))
    for file in files:
        subprocess.run(['arm-none-eabi-gcc', '-mcpu=cortex-m0plus', '-mthumb', '-std=c11', '-ffreestanding', '-Wall', '-Wextra', '-Werror', '-fsyntax-only', str(file)], check=True)
    result = {'result': 'PASS', 'source_sha256': sha(original.read_bytes()), 'binary_sha256': sha(binary),
              'image_bytes': len(binary), 'independent_objcopy_match': True, 'analysis_elf_flash_match': True,
              'c_syntax_checked': [str(f.relative_to(ROOT)) for f in files],
              'limitations': ['Syntax and byte identity do not prove reconstructed firmware links or is behaviorally equivalent.']}
    out = report_path('verification/artifact_result.json')
    out.parent.mkdir(exist_ok=True)
    out.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
