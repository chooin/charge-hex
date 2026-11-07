#!/usr/bin/env python3
"""Package source and evidence locally; does not upload or execute firmware."""
from pathlib import Path
import hashlib
import json
import zipfile

ROOT=Path(__file__).resolve().parents[2]
EXCLUDED={'build','__pycache__','initial_decompile','prior_classification_decompile'}

def main():
    files=[ROOT/'README.md',ROOT/'stm32_fw.hex',ROOT/'主板.png']
    for path in sorted((ROOT/'recovery').rglob('*')):
        if not path.is_file() or EXCLUDED.intersection(path.relative_to(ROOT/'recovery').parts):continue
        if path.suffix in {'.pyc','.o','.a','.so','.dylib'}:continue
        if path.name=='delivery_manifest.json':continue
        files.append(path)
    records=[]
    destination=ROOT/'firmware_recovered_source.zip'
    with zipfile.ZipFile(destination,'w',zipfile.ZIP_DEFLATED,compresslevel=9) as archive:
        for path in files:
            data=path.read_bytes();relative=path.relative_to(ROOT).as_posix()
            archive.writestr(relative,data)
            records.append({'path':relative,'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()})
        manifest={'kind':'firmware-recovery-source-package','original_hex_unchanged':True,'files':records,
                  'excluded':'Compiler products and prior superseded Ghidra exports; no installed tools bundled.'}
        content=json.dumps(manifest,indent=2,ensure_ascii=False)+'\n'
        (ROOT/'recovery/delivery_manifest.json').write_text(content)
        archive.writestr('recovery/delivery_manifest.json',content)
    with zipfile.ZipFile(destination) as archive:
        assert archive.testzip() is None
        for record in records:
            assert hashlib.sha256(archive.read(record['path'])).hexdigest()==record['sha256']
    print(json.dumps({'archive':str(destination),'files':len(records)+1,'bytes':destination.stat().st_size,
                      'sha256':hashlib.sha256(destination.read_bytes()).hexdigest()},indent=2))
if __name__=='__main__': main()
