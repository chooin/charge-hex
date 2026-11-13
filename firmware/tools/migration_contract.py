#!/usr/bin/env python3
"""Check recorded migration contracts against their source dependencies.

These structural checks supplement the independent original-Thumb tests; they
do not establish ABI semantics, dynamic-call completeness or board acceptance.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
CONTRACT = ROOT / 'firmware/platform/apm32/migration.json'
HEX_SHA = '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'


def require(condition, message):
    if not condition:
        raise ValueError(message)


def address(value):
    require(isinstance(value, str) and re.fullmatch(r'0x[0-9a-fA-F]{8}', value),
            f'invalid address: {value!r}')
    return int(value, 16)


def span(value):
    start, end = address(value['start']), address(value['end_exclusive'])
    require(start < end, 'memory region must be nonempty')
    return start, end


def source_file(root, name):
    path = (root / name).resolve()
    require(root.resolve() in path.parents and path.is_file(),
            f'missing or invalid source dependency: {name}')
    return path


def validate_contract(contract, root=ROOT):
    """Validate a loaded manifest; raise ValueError for an unusable contract."""
    try:
        require(contract['schema_version'] == 1, 'unsupported migration schema')
        require(contract['original_hex_sha256'] == HEX_SHA,
                'manifest cannot redefine the original HEX identity')
        require(hashlib.sha256((root / 'stm32_fw.hex').read_bytes()).hexdigest() == HEX_SHA,
                'original HEX identity changed')
        inventory = (root / 'recovery/full_assembly/instructions.json').read_bytes()
        require(hashlib.sha256(inventory).hexdigest() == contract['instruction_inventory_sha256'],
                'instruction inventory differs from reviewed contract')
        instructions = json.loads(inventory)
        instruction_addresses = {address(row['address']) for row in instructions}
        flash = {name: span(contract['flash'][name])
                 for name in ('legacy', 'extension', 'persistent', 'preserved_boot')}
        require(flash['legacy'][1] == flash['extension'][0] and
                flash['extension'][1] == flash['persistent'][0], 'Flash regions are not contiguous')
        require(flash['legacy'][0] == flash['preserved_boot'][0] and
                flash['preserved_boot'][1] <= flash['legacy'][1], 'Boot must be inside legacy region')
        require(flash['preserved_boot'] == (0x08000000, 0x08004000),
                'preserved Boot must retain the established original partition')
        linker = (root / 'firmware/platform/apm32/firmware.ld').read_text()
        for name in ('legacy', 'extension', 'persistent'):
            match = re.search(r'\b' + name.upper() +
                              r'\s*\([^)]*\)\s*:\s*ORIGIN\s*=\s*(0x[\da-fA-F]+),\s*LENGTH\s*=\s*(0x[\da-fA-F]+)', linker)
            require(match is not None, f'linker region not found: {name}')
            start, length = (int(v, 16) for v in match.groups())
            require(flash[name] == (start, start + length), f'linker layout differs: {name}')
        ram_start, ram_end = span(contract['sram'])
        require((ram_start, ram_end) == (0x20000000, 0x20002000),
                'SRAM contract must retain the established 8 KiB device boundary')
        bridge = (root / 'firmware/platform/apm32/legacy_bridge.c').read_text()
        shims = (root / 'firmware/platform/apm32/abi_shims.S').read_text()
        entries = contract['entries']
        require(isinstance(entries, list) and entries, 'migration entries are required')
        seen_addresses, seen_symbols, seen_ids = set(), set(), set()
        windows = []
        for entry in entries:
            name = entry['replacement_symbol']
            start, window = address(entry['original_entry']), entry['window_bytes']
            require(start not in seen_addresses and name not in seen_symbols and
                    entry['id'] not in seen_ids, 'duplicate migration entry, symbol or id')
            seen_addresses.add(start); seen_symbols.add(name); seen_ids.add(entry['id'])
            require(isinstance(name, str) and re.fullmatch(r'charge_legacy_[a-z_]+', name),
                    f'invalid replacement symbol: {name}')
            require(window == 16 and start % 4 == 0, f'{name}: requires a word-aligned 16-byte veneer')
            require(flash['preserved_boot'][1] <= start and start + window <= flash['extension'][0],
                    f'{name}: entry window is outside replaceable App code')
            require(start in instruction_addresses and start + window in instruction_addresses,
                    f'{name}: entry/window does not match instruction boundaries')
            require(all(start + window <= lo or hi <= start for lo, hi in windows),
                    f'{name}: overlapping replacement windows')
            windows.append((start, start + window))
            abi = entry['abi']
            require(abi['standard_preserved'] == ['r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'sp'],
                    f'{name}: standard register contract is missing')
            require(abi['stack_alignment_bytes'] == 8 and bool(abi['return_value']),
                    f'{name}: stack/return contract is missing')
            profiles = {'direct_c': [], 'preserve_ip_entry': ['r12'],
                        'preserve_r3_entry': ['r3', 'r12'], 'storage_read': ['r1', 'r2', 'r12']}
            shim = abi['shim']
            require(shim in profiles and abi['extra_preserved'] == profiles[shim],
                    f'{name}: extra register contract does not match shim profile')
            implementation = name if shim == 'direct_c' else name + '_impl'
            definition = re.search(r'\b' + re.escape(implementation) + r'\s*\(([^;{}]*)\)\s*\{', bridge)
            require(definition is not None, f'{name}: replacement implementation is missing')
            parameters = [] if definition[1].strip() == 'void' else definition[1].split(',')
            require(len(parameters) == len(abi['parameters']), f'{name}: parameter count differs')
            for i, (parameter, declaration) in enumerate(zip(abi['parameters'], parameters)):
                expected_location = f'r{i}' if i < 4 else f'stack+{4 * (i - 4)}'
                require(parameter['location'] == expected_location and parameter['bits'] == 32 and
                        parameter['name'] and parameter['behavior'], f'{name}: parameter contract is incomplete')
                require((parameter['kind'] == 'pointer' and '*' in declaration) or
                        (parameter['kind'] == 'uint32' and 'uint32_t' in declaration and '*' not in declaration),
                        f'{name}: parameter width/kind differs from implementation')
            if shim in ('preserve_ip_entry', 'preserve_r3_entry'):
                require(re.search(r'^' + shim + r'\s+' + re.escape(name) + r'\s*$', shims, re.M),
                        f'{name}: shim invocation is missing')
            elif shim == 'storage_read':
                require(re.search(r'^' + re.escape(name) + r':$', shims, re.M), f'{name}: read shim is missing')
            callers = [address(value) for value in entry['direct_call_sites']]
            observed = [address(row['address']) for row in instructions
                        if row['mnemonic'] == 'bl' and row['operands'] == f'#{hex(start)}']
            require(sorted(callers) == sorted(observed) and callers,
                    f'{name}: classified direct caller inventory differs')
            require(entry['caller_coverage'] and entry['equivalence_scope'] and entry['ownership'],
                    f'{name}: coverage, input-domain and ownership descriptions are required')
            require(entry['state_bindings'], f'{name}: state bindings are required')
            for binding in entry['state_bindings']:
                location, size = address(binding['address']), binding['bytes']
                require(binding['name'] and binding['notes'] and binding['access'] in ('read', 'write', 'read_write'),
                        f'{name}: incomplete state binding')
                require(ram_start <= location < ram_end and
                        (size is None or (type(size) is int and size > 0 and location + size <= ram_end)),
                        f'{name}: state binding is outside SRAM')
                require(re.search(r'\b0x' + f'{location:08x}' + r'u?\b', bridge, re.I),
                        f'{name}: state address is not bound by the platform adapter')
            require(entry['verification'], f'{name}: verification dependencies are required')
            for test in entry['verification']:
                source_file(root, test)
            require(entry['status'] == {'portable_api': 'implemented', 'native_integration': 'integrated',
                                       'board_acceptance': 'unverified'}, f'{name}: unsupported acceptance status')
        require(contract['limitations'], 'scope limitations are required')
    except (KeyError, TypeError) as exc:
        raise ValueError(f'incomplete migration contract: {exc}') from exc
    return contract


def load_contract(path=CONTRACT, root=ROOT):
    return validate_contract(json.loads(Path(path).read_text()), root)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--contract', type=Path, default=CONTRACT)
    args = parser.parse_args()
    try:
        contract = load_contract(args.contract)
    except (ValueError, OSError) as exc:
        parser.exit(1, f'Migration contract rejected: {exc}\n')
    print(f"PASS: {len(contract['entries'])} migration contracts match layout, implementations, "
          "classified callers and verification dependencies; board acceptance remains unverified")


if __name__ == '__main__':
    main()
