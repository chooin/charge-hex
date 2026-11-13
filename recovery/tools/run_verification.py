#!/usr/bin/env python3
"""Run a fresh verification suite and bind its evidence to inputs and tools."""
import argparse
from datetime import datetime, timezone
import hashlib
import json
import os
from pathlib import Path
import platform
import shlex
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
HEX_SHA = '22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf'
REPORTS = {
    'firmware': ['firmware/native_verification.json',
                 'firmware/native_edges_verification.json',
                 'firmware/native_sequences_verification.json'],
    'recovery': ['full_assembly/roundtrip_result.json', 'full_c/verification.json',
                 'full_c/review_boundaries.json', 'verification/whole_recovery_audit.json',
                 'verification/artifact_result.json', 'verification/serial_result.json',
                 'artifacts/verification_semantics.json', 'verification/update_crc_result.json',
                 'verification/application_main_result.json', 'verification/business_result.json'],
}
ARTIFACTS = {
    'firmware': ['firmware/build/charge.' + suffix for suffix in ('elf', 'bin', 'hex')],
    'recovery': ['recovery/full_assembly/build/firmware.' + suffix for suffix in ('elf', 'bin', 'hex')],
}
BUILD_VARIABLES = ('CC', 'AR', 'AS', 'LD', 'OBJCOPY', 'ARM_CC', 'ARM_AS',
                   'ARM_OBJCOPY', 'PYTHON', 'CPPFLAGS', 'CFLAGS', 'WARNINGS', 'ARM_FLAGS')


def now():
    return datetime.now(timezone.utc).isoformat()


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def capture(command, cwd=ROOT):
    try:
        result = subprocess.run(command, cwd=cwd, capture_output=True, text=True,
                                timeout=30)
        return {'command': command, 'exit_code': result.returncode,
                'output': (result.stdout + result.stderr).strip()}
    except (OSError, subprocess.TimeoutExpired) as exc:
        return {'command': command, 'exit_code': None, 'error': str(exc)}


def source_hashes():
    """Include uncommitted source, and also work from a standalone source package."""
    files = {}
    roots = [ROOT / name for name in ('firmware', 'recovery', 'tests') if (ROOT / name).is_dir()]
    for name in ('Makefile', 'stm32_fw.hex', 'requirements-dev.txt'):
        path = ROOT / name
        if path.is_file():
            files[name] = digest(path)
    # These are executable build/check inputs and retained machine evidence.
    # User logs and notes are outputs, not inputs to the verification suite.
    extensions = {'.c', '.h', '.s', '.ld', '.py', '.json', '.jsonl', '.tsv',
                  '.hex', '.bin', '.elf', '.txt', '.csv'}
    for folder, directories, names in (row for root in roots for row in os.walk(root)):
        directories[:] = sorted(d for d in directories if d not in
                                {'.git', '.orca', 'build', '__pycache__', '.venv', 'node_modules'})
        for name in sorted(names):
            path = Path(folder) / name
            if path.is_symlink() or (name != 'Makefile' and path.suffix.lower() not in extensions):
                continue
            files[path.relative_to(ROOT).as_posix()] = digest(path)
    return files


def build_configuration(run, suite):
    fragment = run / 'build-config.mk'
    fragment.write_text(''.join(f'$(info CHARGE_CONFIG_{key}=$({key}))\n'
                                for key in BUILD_VARIABLES) +
                        '.PHONY: verification-build-config\nverification-build-config:\n\t@:\n')
    directories = ['firmware'] if suite == 'firmware' else ['recovery/full_assembly', 'recovery/full_c']
    configuration = {}
    for directory in directories:
        observed = capture(['make', '--no-print-directory', '-s', '-C', directory,
                            '-f', 'Makefile', '-f', str(fragment), 'verification-build-config'])
        if observed['exit_code'] != 0:
            raise RuntimeError(f'Cannot resolve build configuration: {observed}')
        values = {}
        for line in observed['output'].splitlines():
            if line.startswith('CHARGE_CONFIG_'):
                key, value = line[len('CHARGE_CONFIG_'):].split('=', 1)
                values[key] = value
        configuration[directory] = values
    return configuration


def tool_versions(configuration):
    commands = {'make', 'cc', 'clang', 'arm-none-eabi-gcc', 'arm-none-eabi-as',
                'arm-none-eabi-ld', 'arm-none-eabi-objcopy', 'arm-none-eabi-nm'}
    for values in configuration.values():
        commands.update(values[key] for key in BUILD_VARIABLES[:9] if values.get(key))
    versions = {}
    for command in sorted(commands):
        argv = shlex.split(command)
        versions[command] = {'executable': shutil.which(argv[0]),
                             **capture(argv + ['--version'])}
    versions['python'] = {'executable': sys.executable, 'version': sys.version}
    # Record packages from the effective child interpreters, including Make's
    # PYTHON override, rather than assuming they share the runner's environment.
    probe = ('import json,sys; from importlib import metadata; '
             'print(json.dumps({"executable":sys.executable,"version":sys.version,'
             '"packages":{p:metadata.version(p) for p in ("unicorn","capstone")}}))')
    interpreters = {sys.executable} | {v['PYTHON'] for v in configuration.values() if v.get('PYTHON')}
    versions['python_environments'] = {command: capture(shlex.split(command) + ['-c', probe])
                                       for command in sorted(interpreters)}
    return versions


def check_reports(run, suite):
    for name in REPORTS[suite]:
        path = run / name
        if not path.is_file():
            raise RuntimeError(f'Suite produced no current-run report: {name}')
        report = json.loads(path.read_text())
        states = [report['result'] == 'PASS'] if 'result' in report else []
        states += [report[key] is True for key in ('passed', 'byte_identical') if key in report]
        if not states or not all(states) or report.get('failures'):
            raise RuntimeError(f'Verification report did not pass: {name}')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('suite', choices=('firmware', 'recovery', 'all'))
    args = parser.parse_args()
    if not __debug__ or os.environ.get('PYTHONOPTIMIZE') not in (None, '', '0'):
        parser.error('verification requires Python assertions (no -O/PYTHONOPTIMIZE)')
    output = ROOT / 'recovery/build/verification'
    output.mkdir(parents=True, exist_ok=True)
    run = Path(tempfile.mkdtemp(prefix=datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ-'),
                                dir=output))
    manifest = {'schema_version': 1, 'suite': args.suite, 'status': 'RUNNING',
                'started_at': now(), 'run_directory': str(run), 'steps': [],
                'platform': platform.platform(), 'hardware_execution': False,
                'limitations': ['Finite host/emulation checks; no board acceptance.']}
    result_path = run / 'run.json'

    def save():
        temporary = run / 'run.json.tmp'
        temporary.write_text(json.dumps(manifest, indent=2) + '\n')
        temporary.replace(result_path)

    save()
    print(f'Verification run: {run}', flush=True)
    code = 1
    before = None
    try:
        before = source_hashes()
        manifest['input_sha256'] = before
        if before.get('stm32_fw.hex') != HEX_SHA:
            raise RuntimeError('Original HEX identity changed')
        git_root = capture(['git', 'rev-parse', '--show-toplevel'])
        if git_root['exit_code'] == 0 and Path(git_root['output']).resolve() == ROOT:
            manifest['git'] = {'head': capture(['git', 'rev-parse', 'HEAD']),
                               'status': capture(['git', 'status', '--porcelain'])}
        else:
            manifest['git'] = None
        suites = ['firmware', 'recovery'] if args.suite == 'all' else [args.suite]
        configuration = {}
        for suite in suites:
            configuration.update(build_configuration(run, suite))
        manifest['build_configuration'] = configuration
        manifest['tools'] = tool_versions(configuration)
        env = os.environ.copy()
        env['CHARGE_VERIFICATION_DIR'] = str(run)
        code = 0
        for suite in suites:
            # A fresh compile prevents old objects built with different flags
            # from being attributed to this run's recorded configuration.
            command = ['make', '-B'] + (['-C', 'recovery'] if suite == 'recovery' else []) + ['verify-checks']
            log_path = run / f'{suite}.log'
            step = {'suite': suite, 'command': command, 'log': log_path.name,
                    'status': 'RUNNING', 'started_at': now()}
            manifest['steps'].append(step)
            save()
            print(f'Running {suite}; log: {log_path}', flush=True)
            with log_path.open('w') as log:
                completed = subprocess.run(command, cwd=ROOT, env=env,
                                           stdout=log, stderr=subprocess.STDOUT)
            step.update(exit_code=completed.returncode, finished_at=now(),
                        status='FAIL')
            if completed.returncode:
                code = completed.returncode
                break
            check_reports(run, suite)
            step['status'] = 'PASS'
        if code == 0:
            manifest['status'] = 'PASS'
        else:
            manifest['status'] = 'FAIL'
    except KeyboardInterrupt:
        code = 130
        manifest.update(status='INTERRUPTED', error='Verification interrupted')
        if manifest['steps'] and manifest['steps'][-1]['status'] == 'RUNNING':
            manifest['steps'][-1].update(status='INTERRUPTED', finished_at=now())
    except Exception as exc:
        code = 1
        manifest.update(status='FAIL', error=str(exc))
    finally:
        try:
            after = source_hashes()
            if before is not None:
                changed = sorted(name for name in before.keys() | after.keys()
                                 if before.get(name) != after.get(name))
                manifest['changed_inputs'] = changed
                if changed:
                    raise RuntimeError('Inputs changed during verification')
        except (OSError, RuntimeError) as exc:
            code = 1
            manifest.update(status='FAIL', error=str(exc))
        manifest['artifacts'], manifest['artifact_copies'] = {}, {}
        try:
            selected = ('firmware', 'recovery') if args.suite == 'all' else (args.suite,)
            for name in (name for suite in selected for name in ARTIFACTS[suite]):
                if not (ROOT / name).is_file():
                    if manifest['status'] == 'PASS':
                        raise RuntimeError(f'Missing build artifact: {name}')
                    continue
                copy = run / 'artifacts' / name
                copy.parent.mkdir(parents=True, exist_ok=True)
                copy.write_bytes((ROOT / name).read_bytes())
                manifest['artifacts'][name] = digest(copy)
                manifest['artifact_copies'][name] = copy.relative_to(run).as_posix()
                if digest(ROOT / name) != manifest['artifacts'][name]:
                    raise RuntimeError(f'Build artifact changed during archival: {name}')
            if manifest['status'] == 'PASS':
                for suite in selected:
                    image = ARTIFACTS[suite][1]
                    reports = REPORTS['firmware'] if suite == 'firmware' else ['full_assembly/roundtrip_result.json']
                    key = 'native_bin_sha256' if suite == 'firmware' else 'sha256'
                    for name in reports:
                        tested_hash = json.loads((run / name).read_text()).get(key)
                        if tested_hash != manifest['artifacts'][image]:
                            raise RuntimeError(f'Archived image does not match tested image: {name}')
        except (OSError, RuntimeError) as exc:
            code = 1
            manifest.update(status='FAIL', error=f'Cannot retain build artifacts: {exc}')
        manifest['evidence_sha256'] = {p.relative_to(run).as_posix(): digest(p)
                                     for p in sorted(run.rglob('*')) if p.is_file() and p != result_path}
        manifest['finished_at'] = now()
        save()
    print(f"{manifest['status']}: {result_path}", flush=True)
    if manifest.get('error'):
        print(manifest['error'], file=sys.stderr)
    return code


if __name__ == '__main__':
    raise SystemExit(main())
