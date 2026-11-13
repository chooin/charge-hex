#!/usr/bin/env python3
"""Build-only migration adapter; never writes recovery or the input HEX.

Retains original labels/layout, replaces selected public entries with Thumb
tail veneers, and frees the verified FF range for separately linked C code.
The original source remains the oracle, not a second editable implementation.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
from migration_contract import HEX_SHA, load_contract

if not __debug__:
    raise RuntimeError("Run verification without Python optimization (-O)")

ROOT = Path(__file__).resolve().parents[2]
CONTRACT = load_contract()
ENTRIES = {
    int(entry['original_entry'], 16): entry['replacement_symbol']
    for entry in CONTRACT['entries']
}
EXTENSION_START = int(CONTRACT['flash']['extension']['start'], 16)
EXTENSION_END = int(CONTRACT['flash']['extension']['end_exclusive'], 16)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    assert all(entry % 4 == 0 for entry in ENTRIES), "16-byte veneer requires word-aligned entry"
    output = args.output.resolve()
    build = (ROOT / "firmware/build").resolve()
    if build not in output.parents:
        parser.error("generated source must stay under firmware/build")
    assert hashlib.sha256((ROOT / "stm32_fw.hex").read_bytes()).hexdigest() == HEX_SHA, "Original HEX identity changed"
    source = (ROOT / "recovery/full_assembly/firmware.S").read_text()
    # Reject external branches/aliases to the overwritten interior of an entry.
    removed = {addr for start in ENTRIES for addr in range(start + 2, start + 16, 2)}
    for line in source.splitlines():
        if line.startswith(".L_"):
            continue
        address = re.search(r"/\* ([0-9a-f]{8}):", line)
        at = int(address[1], 16) if address else None
        for target in re.findall(r"\.L_([0-9a-f]{8})", line):
            target = int(target, 16)
            if target in removed:
                start = next(x for x in ENTRIES if x < target < x + 16)
                assert at is not None and start <= at < start + 16, f"Referenced overwritten label: {line}"
    result, seen, erased = [], set(), 0
    for line in source.splitlines():
        label = re.fullmatch(r"\.L_([0-9a-f]{8}):", line)
        address = re.search(r"/\* ([0-9a-f]{8}):", line)
        at = int((label or address)[1], 16) if label or address else None
        if at == EXTENSION_END and label:
            result.append('.section .persistent,"a",%progbits')
        if at is not None and EXTENSION_START <= at < EXTENSION_END:
            if address:
                assert ".word 0xffffffff" in line and "explicit-FF-fill" in line
                erased += 4
            continue
        start = next((x for x in ENTRIES if at is not None and x <= at < x + 16), None)
        if start is not None:
            if at == start and label:
                seen.add(start)
                result.extend([line, "    push {r3, lr}", "    ldr r3, [pc, #8]",
                               "    str r3, [sp, #4]", "    pop {r3, pc}", "    nop", "    nop",
                               f"    .word {ENTRIES[start]}"])
            continue
        result.append(line)
        if line.startswith('.section .firmware'):
            result.append('    .balign 4')
        if line.startswith('.global fw_'):
            result.append(f'.type {line.split()[1]}, %function')
    assert seen == set(ENTRIES)
    assert erased == EXTENSION_END - EXTENSION_START
    output.parent.mkdir(parents=True, exist_ok=True)
    result.append('.section .note.GNU-stack,"",%progbits')
    output.write_text("\n".join(result) + "\n")
    output.with_suffix(".json").write_text(json.dumps({
        "source_sha256": hashlib.sha256(source.encode()).hexdigest(),
        "entries": {hex(k): v for k, v in ENTRIES.items()},
        "extension": [hex(EXTENSION_START), hex(EXTENSION_END)],
    }, indent=2) + "\n")

if __name__ == "__main__":
    main()
