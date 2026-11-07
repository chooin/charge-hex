#!/usr/bin/env python3
"""Reproduce REA/Ghidra's function export without changing global MCP settings."""
import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[2]

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--output', type=Path, default=ROOT / 'recovery/decompiled')
    ap.add_argument('--ghidra', type=Path, default=Path(os.environ.get('GHIDRA_INSTALL_DIR', str(Path.home()/'.cache/firmware-recovery-tools/ghidra_12.1.4_PUBLIC'))))
    ap.add_argument('--java-home', type=Path, default=Path(os.environ.get('JAVA_HOME', '/opt/homebrew/opt/openjdk/libexec/openjdk.jdk/Contents/Home')))
    args = ap.parse_args()
    rea = shutil.which('rea')
    if rea is None: raise SystemExit('REA CLI is required')
    if not (args.ghidra/'support/analyzeHeadless').is_file(): raise SystemExit('Set --ghidra to an extracted Ghidra 12.1.x installation')
    env = os.environ.copy()
    env.update(GHIDRA_INSTALL_DIR=str(args.ghidra.resolve()), JAVA_HOME=str(args.java_home.resolve()),
               REA_GHIDRA_LANGUAGE_ID='ARM:LE:32:Cortex',
               REA_GHIDRA_SEED_FILE=str(ROOT/'recovery/ghidra/seeds.tsv'),
               REA_GHIDRA_DECOMPILE_TIMEOUT_SECONDS='30')
    command = [rea, 'decompile-all', str(ROOT/'recovery/full_assembly/build/firmware.elf'),
               '--provider','ghidra','--output',str(args.output.resolve()),'--format','json']
    if args.output.exists(): command.append('--resume')
    result = subprocess.run(command, env=env, capture_output=True, text=True)
    log = ROOT/'recovery/ghidra/reproduce.log'
    log.write_text(result.stderr)
    output = ROOT/'recovery/ghidra/reproduce-result.json'
    output.write_text(result.stdout)
    if result.returncode: raise SystemExit(f'REA failed; inspect {log} and {output}')
    record=json.loads(result.stdout)
    print(json.dumps(record.get('normalized_result',record), indent=2))

if __name__=='__main__': main()
