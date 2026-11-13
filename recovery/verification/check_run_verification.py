#!/usr/bin/env python3
"""Exercise verification-run acceptance without invoking real builds or emulation."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
NATIVE_REPORTS = ('native_verification.json', 'native_edges_verification.json',
                  'native_sequences_verification.json')

MAKE_STUB = r'''
import hashlib
import json
import os
from pathlib import Path
import signal
import sys
import time

if '--version' in sys.argv:
    print(Path(sys.argv[0]).name + ' controlled-tool 1.0')
    raise SystemExit(0)
if 'verification-build-config' in sys.argv:
    print('CHARGE_CONFIG_CC=cc')
    print('CHARGE_CONFIG_ARM_CC=arm-none-eabi-gcc')
    print('CHARGE_CONFIG_CFLAGS=-O2')
    print('CHARGE_CONFIG_ARM_FLAGS=-Os -mcpu=cortex-m0plus')
    raise SystemExit(0)
if 'verify-checks' not in sys.argv or '-B' not in sys.argv:
    raise SystemExit('Expected a forced verification build')
mode = os.environ.get('CHARGE_RUN_TEST_MODE', 'pass')
run = Path(os.environ['CHARGE_VERIFICATION_DIR'])
if mode == 'interrupt':
    os.kill(os.getppid(), signal.SIGINT)
    time.sleep(0.5)
    raise SystemExit(1)
if mode == 'fail':
    print('controlled build failure')
    raise SystemExit(7)
suite = 'recovery' if '-C' in sys.argv else 'firmware'
reports = (['full_assembly/roundtrip_result.json', 'full_c/verification.json',
            'full_c/review_boundaries.json', 'verification/whole_recovery_audit.json',
            'verification/artifact_result.json', 'verification/serial_result.json',
            'artifacts/verification_semantics.json', 'verification/update_crc_result.json',
            'verification/application_main_result.json', 'verification/business_result.json']
           if suite == 'recovery' else
           ['firmware/native_verification.json', 'firmware/native_edges_verification.json',
            'firmware/native_sequences_verification.json'])
if mode != 'missing':
    for name in reports:
        target = run / name
        target.parent.mkdir(parents=True, exist_ok=True)
        report = {'result': 'FAIL' if mode == 'bad-report' else 'PASS', 'fixture': suite}
        image_hash = hashlib.sha256(b'controlled image').hexdigest()
        if suite == 'firmware':
            report['native_bin_sha256'] = '0' * 64 if mode == 'wrong-artifact' else image_hash
        elif name == 'full_assembly/roundtrip_result.json':
            report['sha256'] = image_hash
        target.write_text(json.dumps(report))
build = Path('firmware/build' if suite == 'firmware' else 'recovery/full_assembly/build')
build.mkdir(parents=True, exist_ok=True)
if mode != 'missing-artifacts':
    for extension in ('bin', 'elf', 'hex'):
        (build / (('charge.' if suite == 'firmware' else 'firmware.') + extension)).write_bytes(b'controlled image')
if mode == 'changed':
    Path('firmware/source.c').write_text('changed during verification\n')
if mode == 'deleted':
    Path('firmware/source.c').unlink()
print('controlled ' + suite + ' checks passed')
'''


class VerificationRunTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix='verification-run-test-')
        self.addCleanup(temporary.cleanup)
        self.root = Path(temporary.name).resolve()
        self.runner = self.root / 'recovery/tools/run_verification.py'
        self.runner.parent.mkdir(parents=True)
        shutil.copyfile(ROOT / 'recovery/tools/run_verification.py', self.runner)
        # This is a separate read-only input copy; the repository oracle is untouched.
        shutil.copyfile(ROOT / 'stm32_fw.hex', self.root / 'stm32_fw.hex')
        (self.root / 'firmware').mkdir()
        (self.root / 'firmware/source.c').write_text('original source\n')
        self.bin = self.root / 'bin'
        self.bin.mkdir()
        for tool in ('make', 'cc', 'clang', 'arm-none-eabi-gcc', 'arm-none-eabi-as',
                     'arm-none-eabi-ld', 'arm-none-eabi-objcopy', 'arm-none-eabi-nm'):
            path = self.bin / tool
            path.write_text(f'#!{sys.executable}\n' + MAKE_STUB)
            path.chmod(0o755)
        self.runs = self.root / 'recovery/build/verification'

    def run_suite(self, *, mode='pass', suite='firmware', redirect_stdout=False):
        previous = set(self.runs.glob('*/run.json'))
        env = os.environ.copy()
        env.update(PATH=str(self.bin) + os.pathsep + env.get('PATH', ''),
                   CHARGE_RUN_TEST_MODE=mode)
        env.pop('PYTHONOPTIMIZE', None)
        command = [sys.executable, str(self.runner), suite]
        if redirect_stdout:
            with (self.root / 'verify.log').open('w') as output:
                result = subprocess.run(command, cwd=self.root, env=env, stdout=output,
                                        stderr=subprocess.PIPE, text=True)
        else:
            result = subprocess.run(command, cwd=self.root, env=env, capture_output=True, text=True)
        fresh = set(self.runs.glob('*/run.json')) - previous
        self.assertEqual(len(fresh), 1, (result.stdout or '') + result.stderr)
        path = fresh.pop()
        return result, path.parent, json.loads(path.read_text())

    def test_success_binds_inputs_tools_configuration_and_artifacts(self):
        result, run, manifest = self.run_suite()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(manifest['status'], 'PASS')
        self.assertFalse(manifest['hardware_execution'])
        self.assertEqual(manifest['changed_inputs'], [])
        self.assertEqual(manifest['input_sha256']['firmware/source.c'],
                         hashlib.sha256(b'original source\n').hexdigest())
        self.assertEqual(manifest['build_configuration']['firmware']['CFLAGS'], '-O2')
        self.assertIn('controlled-tool 1.0', manifest['tools']['cc']['output'])
        self.assertIn('controlled-tool 1.0', manifest['tools']['clang']['output'])
        self.assertIn('controlled-tool 1.0', manifest['tools']['arm-none-eabi-nm']['output'])
        self.assertEqual(manifest['artifacts']['firmware/build/charge.bin'],
                         hashlib.sha256(b'controlled image').hexdigest())
        retained = run / manifest['artifact_copies']['firmware/build/charge.bin']
        self.assertEqual(retained.read_bytes(), b'controlled image')
        for name in NATIVE_REPORTS:
            relative = 'firmware/' + name
            self.assertTrue((run / relative).is_file())
            self.assertEqual(manifest['evidence_sha256'][relative],
                             hashlib.sha256((run / relative).read_bytes()).hexdigest())

    def test_failure_stops_all_suite_and_preserves_log(self):
        result, run, manifest = self.run_suite(mode='fail', suite='all')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertEqual(len(manifest['steps']), 1)
        self.assertEqual(manifest['steps'][0]['exit_code'], 7)
        self.assertIn('controlled build failure', (run / 'firmware.log').read_text())
        self.assertFalse((run / 'recovery.log').exists())

    def test_missing_current_reports_cannot_use_previous_pass(self):
        result, previous, manifest = self.run_suite()
        self.assertEqual(result.returncode, 0, result.stderr)
        result, current, manifest = self.run_suite(mode='missing')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertIn('current-run report', manifest['error'])
        self.assertNotEqual(previous, current)
        self.assertTrue((previous / 'firmware/native_verification.json').is_file())

    def test_changed_source_invalidates_otherwise_successful_checks(self):
        result, run, manifest = self.run_suite(mode='changed')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertIn('firmware/source.c', manifest['changed_inputs'])
        self.assertTrue((run / 'firmware/native_verification.json').is_file())

    def test_deleted_input_finishes_with_failed_manifest(self):
        result, run, manifest = self.run_suite(mode='deleted')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertIn('firmware/source.c', manifest['changed_inputs'])
        self.assertIn('finished_at', manifest)

    def test_failed_report_is_rejected_despite_successful_process(self):
        result, run, manifest = self.run_suite(mode='bad-report')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertEqual(manifest['steps'][0]['exit_code'], 0)
        self.assertIn('native_verification.json', manifest['error'])

    def test_interruption_retains_an_incomplete_run(self):
        result, run, manifest = self.run_suite(mode='interrupt')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'INTERRUPTED')
        self.assertIn('finished_at', manifest)
        self.assertFalse((run / 'firmware/native_verification.json').exists())

    def test_redirected_root_log_is_output_not_source(self):
        result, run, manifest = self.run_suite(redirect_stdout=True)
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(manifest['status'], 'PASS')
        self.assertNotIn('verify.log', manifest['input_sha256'])
        self.assertEqual(manifest['changed_inputs'], [])
        self.assertIn('PASS', (self.root / 'verify.log').read_text())

    def test_missing_artifacts_cannot_pass_on_reports_alone(self):
        result, run, manifest = self.run_suite(mode='missing-artifacts')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertIn('Missing build artifact', manifest['error'])
        self.assertTrue((run / 'firmware/native_verification.json').is_file())

    def test_retained_binary_must_match_tested_identity(self):
        result, run, manifest = self.run_suite(mode='wrong-artifact')
        self.assertNotEqual(result.returncode, 0)
        self.assertEqual(manifest['status'], 'FAIL')
        self.assertIn('does not match tested image', manifest['error'])
        self.assertIn('firmware/build/charge.bin', manifest['artifacts'])

    def test_repeated_successes_have_independent_run_directories(self):
        result, first, before = self.run_suite()
        self.assertEqual(result.returncode, 0, result.stderr)
        original_manifest = (first / 'run.json').read_bytes()
        result, second, after = self.run_suite()
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertNotEqual(first, second)
        self.assertEqual((first / 'run.json').read_bytes(), original_manifest)
        self.assertEqual(after['status'], 'PASS')

    def test_all_runs_both_suites_in_one_evidence_directory(self):
        result, run, manifest = self.run_suite(suite='all')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(manifest['status'], 'PASS')
        self.assertEqual([step['suite'] for step in manifest['steps']], ['firmware', 'recovery'])
        self.assertTrue((run / 'firmware/native_verification.json').is_file())
        self.assertTrue((run / 'full_c/verification.json').is_file())
        self.assertIn('recovery/full_c', manifest['build_configuration'])


if __name__ == '__main__':
    unittest.main(verbosity=2)
