"""Keep fresh verification output separate from committed recovery evidence."""
from datetime import datetime, timezone
import os
from pathlib import Path
import sys
import tempfile

RECOVERY = Path(__file__).resolve().parents[1]
RUN_ENV = 'CHARGE_VERIFICATION_DIR'
_run_directory = None


def run_directory():
    """Use the suite's run directory, or allocate one for this standalone command."""
    global _run_directory
    if _run_directory is None:
        configured = os.environ.get(RUN_ENV)
        if configured:
            _run_directory = Path(configured).resolve()
            _run_directory.mkdir(parents=True, exist_ok=True)
        else:
            parent = RECOVERY / 'build/verification'
            parent.mkdir(parents=True, exist_ok=True)
            stamp = datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%SZ-')
            _run_directory = Path(tempfile.mkdtemp(prefix=stamp, dir=parent))
        print(f'Verification output: {_run_directory}', file=sys.stderr)
    return _run_directory


def _relative_path(relative):
    path = Path(relative)
    if path.is_absolute() or '..' in path.parts or path == Path('.'):
        raise ValueError('report path must be a nonempty relative path within the run')
    return path


def report_path(relative):
    """Return a writable run-local path using the original recovery-relative name."""
    root = run_directory()
    path = root / _relative_path(relative)
    if root not in path.resolve().parents:
        raise ValueError('report path escapes the verification run')
    path.parent.mkdir(parents=True, exist_ok=True)
    return path


def verification_input(relative, historical):
    """Never substitute a historical PASS for a missing result in an explicit run."""
    if os.environ.get(RUN_ENV):
        path = run_directory() / _relative_path(relative)
        if not path.is_file():
            raise FileNotFoundError(f'Missing verification result in this run: {path}')
        return path, 'current_run'
    return Path(historical), 'historical_snapshot'
