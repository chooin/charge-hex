# Migration contracts and verification runs

The native image still uses the same seven replacements. This change makes their
integration requirements explicit without changing runtime C, assembly or the linker.

## Registration boundary

`firmware/platform/apm32/migration.json` records the reviewed original image and
instruction inventory, Flash/SRAM regions, replacement symbols, 16-byte entry windows,
raw parameter widths, shim profiles, state bindings, classified direct call sites,
verification dependencies and acceptance status. Unknown handle extents remain null;
board acceptance is explicitly unverified.

`firmware/tools/migration_contract.py` checks this registration against the original
HEX identity, instruction inventory, platform declarations, shim registrations and
linker regions. Both `make native` and direct ELF builds check it. `prepare_legacy.py`
reads the registered entries and extension range; its generated assembly is unchanged.

These are structural checks. They do not prove a shim's instruction semantics or
complete dynamic callers. The native tests retain independently declared expected
entries and original-Thumb behavior as a separate oracle. Adding an entry requires
reviewing both its registration and those independent scenarios. Never update the
original HEX digest to accommodate a different input image.

## Run boundary

`make verify`, `make verify-recovery`, and
`python3 recovery/tools/run_verification.py all` allocate fresh directories under
`recovery/build/verification/`. The coordinator passes `CHARGE_VERIFICATION_DIR` to
child checks and uses `make -B` so changed compiler flags cannot reuse stale objects.

Each run retains:

- `run.json`: source hashes including uncommitted files, Git context when available,
  effective Make variables, tool versions, requested suite, completed steps and status;
- suite logs with the actual expanded build commands and test output;
- reports grouped by original component, and copies/hashes of observed firmware images.

A run starts RUNNING and only reaches PASS after all requested steps and required
reports pass, the input snapshot remains unchanged, and required archived images match
the BIN identities in those test reports. Source snapshots cover build/check inputs and
machine evidence, excluding user logs and notes. Failure or interruption leaves
an explicit non-PASS result; missing current output cannot be supplied by an older run.
Artifacts retained after a failed run are diagnostic observations, not accepted builds.
Use a separate checkout for concurrent builds with different compiler settings; build
directories are shared by ordinary Make commands within a checkout.

`recovery/tools/reporting.py` routes existing verification outputs without altering
test scenarios. Within a suite, recovery audit requires that run's C model result.
Standalone scripts allocate their own output directory; standalone audit can read the
recorded model result but labels it `historical_snapshot`, including its digest and path.
Standalone results do not claim that the complete suite was executed.

Committed historical reports and decompiler files remain immutable inputs to ordinary
verification. Promoting a new run to a reviewed historical record is a separate,
explicit repository change. Source generators and packaging are separate maintenance
commands; they are not invoked by verification.

## Scope

This infrastructure does not change scheduling, interrupt ownership, protocol rules,
storage layout or hardware drivers. Compiler versions are recorded rather than silently
installed or upgraded. Existing macOS-only host-model checks retain that limitation.
All host/emulation results remain distinct from board acceptance.
