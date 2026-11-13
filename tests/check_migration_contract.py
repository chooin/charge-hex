#!/usr/bin/env python3
"""Reject incomplete or inconsistent migration registration before native build."""
import copy
import json
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'firmware/tools'))
from migration_contract import CONTRACT, load_contract, validate_contract


class MigrationContractTests(unittest.TestCase):
    def setUp(self):
        self.contract = json.loads(CONTRACT.read_text())

    def reject(self, fragment):
        with self.assertRaisesRegex(ValueError, fragment):
            validate_contract(self.contract)

    def test_current_registration_matches_sources(self):
        contract = load_contract()
        self.assertEqual(len(contract['entries']), 7)
        self.assertEqual(sum(len(e['direct_call_sites']) for e in contract['entries']), 34)

    def test_missing_abi_is_rejected(self):
        del self.contract['entries'][0]['abi']
        self.reject('incomplete migration contract')

    def test_missing_verification_is_rejected(self):
        self.contract['entries'][0]['verification'] = []
        self.reject('verification dependencies are required')

    def test_nonexistent_verification_is_rejected(self):
        self.contract['entries'][0]['verification'] = ['tests/not_a_real_check.py']
        self.reject('missing or invalid source dependency')

    def test_unknown_replacement_symbol_is_rejected(self):
        self.contract['entries'][0]['replacement_symbol'] = 'charge_legacy_missing'
        self.reject('replacement implementation is missing')

    def test_original_identity_cannot_be_redefined(self):
        self.contract['original_hex_sha256'] = '0' * 64
        self.reject('cannot redefine')

    def test_duplicate_entry_is_rejected(self):
        self.contract['entries'].append(copy.deepcopy(self.contract['entries'][0]))
        self.reject('duplicate migration')

    def test_entry_cannot_overwrite_boot(self):
        self.contract['entries'][0]['original_entry'] = '0x08000100'
        self.reject('outside replaceable App code')

    def test_boot_protection_cannot_be_shrunk(self):
        self.contract['flash']['preserved_boot']['end_exclusive'] = '0x08002000'
        self.reject('preserved Boot must retain')

    def test_window_size_must_match_veneer(self):
        self.contract['entries'][0]['window_bytes'] = 18
        self.reject('16-byte veneer')

    def test_layout_must_match_linker(self):
        self.contract['flash']['legacy']['end_exclusive'] = '0x0800c000'
        self.contract['flash']['extension']['start'] = '0x0800c000'
        self.reject('linker layout differs')

    def test_register_contract_must_match_shim(self):
        self.contract['entries'][0]['abi']['extra_preserved'] = ['r12']
        self.reject('extra register contract')

    def test_parameter_width_cannot_silently_narrow(self):
        self.contract['entries'][0]['abi']['parameters'][0]['bits'] = 16
        self.reject('parameter contract is incomplete')

    def test_fifth_argument_keeps_stack_location(self):
        entry = next(e for e in self.contract['entries'] if e['id'] == 'send_frame')
        entry['abi']['parameters'][4]['location'] = 'r4'
        self.reject('parameter contract is incomplete')

    def test_classified_callers_cannot_be_omitted(self):
        self.contract['entries'][0]['direct_call_sites'].pop()
        self.reject('caller inventory differs')

    def test_state_binding_must_fit_real_sram(self):
        entry = next(e for e in self.contract['entries'] if e['id'] == 'send_frame')
        entry['state_bindings'][0]['bytes'] = 65536
        self.reject('state binding is outside SRAM')

    def test_state_binding_must_exist_in_platform(self):
        self.contract['entries'][0]['state_bindings'][0]['address'] = '0x20001f00'
        self.reject('state address is not bound')

    def test_board_acceptance_is_not_inferred_from_registration(self):
        self.contract['entries'][0]['status']['board_acceptance'] = 'accepted'
        self.reject('unsupported acceptance status')


if __name__ == '__main__':
    unittest.main(verbosity=2)
