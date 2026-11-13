#!/usr/bin/env python3
"""Exercise recovery CLI acceptance using temporary artifacts and a controlled REA."""
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


def sha(data):
    return hashlib.sha256(data).hexdigest()


class RecoveryWorkflowTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix='recovery-workflow-test-')
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name)
        self.recovery = self.root / 'recovery'
        for name in ('ghidra/export_all.py', 'tools/audit_recovery.py'):
            destination = self.recovery / name
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(ROOT / 'recovery' / name, destination)

    def write(self, relative, data):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        return path

    def write_json(self, relative, value):
        return self.write(relative, json.dumps(value).encode())

    def run_cli(self, script, *args, env=None):
        return subprocess.run(
            [sys.executable, str(self.recovery / script), *map(str, args)],
            cwd=self.root, env=env, capture_output=True, text=True,
        )

    def export(self, *, failed=0, remaining=0, skipped=0, exit_code=0):
        counts = {
            'selected': 3, 'excluded': 0, 'requested': 3 - skipped - remaining,
            'written': 3 - skipped - remaining - failed, 'failed': failed,
            'external': 0, 'skipped': skipped, 'remaining': remaining,
        }
        record = json.dumps({'normalized_result': {'counts': counts}}) + '\n'
        self.write('response.json', record.encode())
        rea = self.write('bin/rea', (
            f'#!{sys.executable}\n'
            'from pathlib import Path\n'
            'import os, sys\n'
            'sys.stdout.write(Path(os.environ["REA_TEST_RESPONSE"]).read_text())\n'
            'sys.stderr.write("controlled REA diagnostics\\n")\n'
            'sys.exit(int(os.environ["REA_TEST_EXIT"]))\n'
        ).encode())
        rea.chmod(0o755)
        self.write('ghidra/support/analyzeHeadless', b'')
        output = self.root / 'export'
        if skipped:
            output.mkdir()
        env = os.environ.copy()
        env.update(
            PATH=str(rea.parent) + os.pathsep + env.get('PATH', ''),
            REA_TEST_RESPONSE=str(self.root / 'response.json'),
            REA_TEST_EXIT=str(exit_code),
        )
        result = self.run_cli(
            'ghidra/export_all.py', '--output', output,
            '--ghidra', self.root / 'ghidra', '--java-home', self.root,
            env=env,
        )
        self.assertEqual((self.recovery / 'ghidra/reproduce-result.json').read_text(), record)
        self.assertEqual((self.recovery / 'ghidra/reproduce.log').read_text(),
                         'controlled REA diagnostics\n')
        return result

    def test_complete_export_succeeds(self):
        result = self.export()
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_partial_export_fails_even_when_rea_exits_zero(self):
        self.assertNotEqual(self.export(failed=1).returncode, 0)

    def test_unfinished_export_fails_even_without_function_errors(self):
        self.assertNotEqual(self.export(remaining=1).returncode, 0)

    def test_fully_verified_resume_succeeds_without_new_writes(self):
        result = self.export(skipped=3)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_rea_process_failure_preserves_diagnostics(self):
        self.assertNotEqual(self.export(exit_code=1).returncode, 0)

    def audit_fixture(self):
        self.write('recovery/artifacts/firmware.bin', b'flash bytes')
        self.write('recovery/full_assembly/build/firmware.bin', b'flash bytes')
        target = b'analysis ELF identity'
        self.write('recovery/full_assembly/build/firmware.elf', target)
        instructions = self.write_json('recovery/full_assembly/instructions.json',
                                       [{'address': '0x80000b4', 'size': 2}])
        source = self.write('recovery/full_c/firmware_model.c', b'model source')
        self.write_json('recovery/full_c/coverage.json', {
            'instruction_inventory_sha256': sha(instructions.read_bytes()),
            'translated_instructions': 1, 'untranslated_mnemonics': [],
        })
        self.write_json('recovery/full_c/verification.json', {
            'result': 'PASS', 'model_source_sha256': sha(source.read_bytes()),
        })
        self.write('recovery/verification/whole_recovery_audit.json', b'original report')
        self.write('recovery/decompiled/README.md', b'original README')
        for directory, names in [('recovery/decompiled', ['old']),
                                 ('build/export with spaces', ['fresh', 'extra'])]:
            functions = []
            for index, name in enumerate(names):
                relative = f'functions/{name}.c'
                file = self.write(f'{directory}/{relative}', f'void {name}(void) {{}}\n'.encode())
                address = hex(0x80000b4 + index * 2)
                functions.append({
                    'address': address, 'name': name, 'status': 'written',
                    'relative_path': relative, 'sha256': sha(file.read_bytes()),
                    'body': {'ranges': [{'start': address, 'end': hex(int(address, 16) + 1)}]},
                })
            self.write_json(f'{directory}/decompile-index.json', {
                'target_sha256': sha(target), 'functions': functions,
            })
        return self.root / 'build/export with spaces'

    def assert_readme_report_link(self, directory, report):
        readme = (directory / 'README.md').read_text()
        match = re.search(r'\[whole_recovery_audit\.json\]\(([^)]+)\)', readme)
        self.assertIsNotNone(match, readme)
        self.assertEqual((directory / match.group(1)).resolve(), report.resolve())

    def assert_original_outputs_unchanged(self):
        self.assertEqual((self.recovery / 'decompiled/README.md').read_bytes(), b'original README')
        self.assertEqual((self.recovery / 'verification/whole_recovery_audit.json').read_bytes(),
                         b'original report')

    def test_default_audit_keeps_existing_output_locations(self):
        self.audit_fixture()
        result = self.run_cli('tools/audit_recovery.py')
        self.assertEqual(result.returncode, 0, result.stderr)
        report = self.recovery / 'verification/whole_recovery_audit.json'
        self.assertEqual(json.loads(report.read_text())['decompiled_functions'], 1)
        self.assert_readme_report_link(self.recovery / 'decompiled', report)

    def test_custom_audit_reads_and_reports_only_selected_export(self):
        directory = self.audit_fixture()
        result = self.run_cli('tools/audit_recovery.py', '--decompiled-dir',
                              directory.relative_to(self.root))
        self.assertEqual(result.returncode, 0, result.stderr)
        report = directory / 'whole_recovery_audit.json'
        self.assertEqual(json.loads(report.read_text())['decompiled_functions'], 2)
        self.assert_readme_report_link(directory, report)
        self.assertIn('functions/fresh.c', (directory / 'README.md').read_text())
        self.assert_original_outputs_unchanged()

    def test_custom_export_corruption_fails_despite_valid_old_export(self):
        directory = self.audit_fixture()
        (directory / 'functions/fresh.c').write_bytes(b'changed after export')
        result = self.run_cli('tools/audit_recovery.py', '--decompiled-dir', directory)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('export content changed', result.stderr)
        self.assertFalse((directory / 'whole_recovery_audit.json').exists())
        self.assert_original_outputs_unchanged()


if __name__ == '__main__':
    unittest.main(verbosity=2)
