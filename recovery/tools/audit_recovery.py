#!/usr/bin/env python3
"""Audit byte identity and export coverage, without treating coverage as correctness."""
import argparse
from pathlib import Path
import hashlib
import json
import os

ROOT=Path(__file__).resolve().parents[1]
def sha(b): return hashlib.sha256(b).hexdigest()
def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--decompiled-dir', type=Path, default=ROOT/'decompiled',
                    help='REA export directory to audit; defaults to the recorded export')
    args=ap.parse_args()
    decompiled=args.decompiled_dir.resolve()
    # Fresh exports keep their reports alongside their own index and README.
    # Preserve the historical report location for the default export only.
    report_path=(ROOT/'verification/whole_recovery_audit.json'
                 if decompiled==(ROOT/'decompiled').resolve()
                 else decompiled/'whole_recovery_audit.json')
    binary=(ROOT/'artifacts/firmware.bin').read_bytes()
    rebuilt=(ROOT/'full_assembly/build/firmware.bin').read_bytes()
    assert binary==rebuilt, 'complete reconstruction byte mismatch'
    index=json.loads((decompiled/'decompile-index.json').read_text())
    target=(ROOT/'full_assembly/build/firmware.elf').read_bytes()
    assert sha(target)==index['target_sha256'], 'export belongs to a different analysis ELF'
    body=set();warnings=[];functions=[]
    for item in index['functions']:
        assert item['status']=='written',item
        path=decompiled/item['relative_path']
        assert sha(path.read_bytes())==item['sha256'], f'export content changed: {path}'
        for r in item.get('body',{}).get('ranges',[]):
            body.update(range(int(r['start'],16),int(r['end'],16)+1))
        for line in path.read_text().splitlines():
            if 'WARNING' in line:
                warnings.append({'file':item['relative_path'],'address':item['address'],'warning':line})
        functions.append({'address':item['address'],'name':item['name'],'file':item['relative_path']})
    instructions=json.loads((ROOT/'full_assembly/instructions.json').read_text())
    model_coverage=json.loads((ROOT/'full_c/coverage.json').read_text())
    model_verification=json.loads((ROOT/'full_c/verification.json').read_text())
    assert model_coverage['instruction_inventory_sha256']==sha((ROOT/'full_assembly/instructions.json').read_bytes()), 'C model generated from stale instruction inventory'
    assert model_coverage['translated_instructions']==len(instructions)
    assert model_coverage['untranslated_mnemonics']==[]
    assert model_verification['result']=='PASS'
    assert model_verification['model_source_sha256']==sha((ROOT/'full_c/firmware_model.c').read_bytes()), 'C model source differs from tested version'
    missing=[];count=0
    for instruction in instructions:
        address=int(instruction['address'],16)
        if all(address+i in body for i in range(instruction['size'])):count+=1
        else:missing.append(instruction)
    report={'firmware_sha256':sha(binary),'rebuilt_sha256':sha(rebuilt),'byte_identical':True,
        'decompiled_functions':len(functions),'all_export_file_hashes_match':True,
        'classified_instructions':len(instructions),'instructions_within_decompiler_bodies':count,
        'whole_c_model_covers_inventory':True,'whole_c_model_matches_verified_source':True,
        'instructions_outside_decompiler_bodies':missing,'decompiler_warnings':warnings,
        'limitations':['Function bodies and code/data labels are analysis results, not original source metadata.',
                      'A successful C pseudocode export is not a successful C compilation or semantic equivalence proof.',
                      'Byte identity verifies the assembly build. C semantic tests have separate finite coverage.']}
    report_path.write_text(json.dumps(report,indent=2)+'\n')
    report_link=Path(os.path.relpath(report_path, decompiled)).as_posix()
    text=['# 全函数 C 反编译索引','',
      '由 REA + Ghidra 12.1.4 从重建 ELF 导出。保留自动生成名称和警告；这批文件是 C 反编译参考，不能直接当作可链接的 MCU C 工程。',
      '',f'共 {len(functions)} 个识别函数。覆盖/警告审计见 [whole_recovery_audit.json]({report_link})。',
      '', '| 地址 | 分析名称 | C 文件 |','|---|---|---|']
    for f in functions:text.append(f"| `{f['address']}` | `{f['name']}` | [{Path(f['file']).name}]({f['file']}) |")
    (decompiled/'README.md').write_text('\n'.join(text)+'\n')
    print(f'Audited export: {decompiled}')
    print(json.dumps({k:v for k,v in report.items() if k not in ['decompiler_warnings','instructions_outside_decompiler_bodies']},indent=2))
    print('outside body instructions:',len(missing),'warning lines:',len(warnings))
if __name__=='__main__':main()
