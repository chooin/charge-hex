# Reliability

## Established verification boundaries

The original HEX is an immutable oracle. Recovery assembly aims at exact decoded Flash
identity; current firmware intentionally changes seven entry windows and an App extension.
Host behavior, original-Thumb comparison, native-image execution, and hardware acceptance
are separate evidence levels. See [Architecture](../ARCHITECTURE.md).

The [existing verification record](verification.md) reports passing development/recovery
checks on 2026-11-07. Those results were not rerun during Knowledge Store creation.
Only source/document checks and the original HEX identity check were performed here.

## Reproducible command map

Run these commands from the repository root when validating implementation work:

| Command | Coverage / output |
| --- | --- |
| make host | C11 library at firmware/build/libcharge.a |
| make native | ARM charge.elf, charge.bin, charge.hex |
| make test | Host C tests, architecture constraints, protocol/config and domain/service differential tests |
| make verify | Build, all tests above, native entry/layout/caller checks, storage/config edges and persistent state sequences |
| make verify-recovery | Independent recovery assembly/model/artifact and selected behavior checks |

Sources: [root Makefile](../Makefile), [firmware Makefile](../firmware/Makefile),
[recovery Makefile](../recovery/Makefile).

Tools: system C compiler, Make, Python 3.9+, GNU Arm Embedded GCC/binutils.
Differential dependencies are pinned in [requirements-dev.txt](../requirements-dev.txt):
Unicorn 2.1.4 and Capstone 5.0.7. Python is host tooling, not a firmware dependency.
Some historical recovery model checks use macOS-specific dynamic-library flags.
Run assertion-based verification without Python -O or PYTHONOPTIMIZE.

The native check writes firmware/build/native_verification.json with source/build
and output hashes. That generated result must correspond to the code being reviewed.
The extended [edge suite](../tests/check_native_edges.py) and
[sequence suite](../tests/check_native_sequences.py) additionally write
native_edges_verification.json and native_sequences_verification.json in the same
build directory. They compare actual original/new ARM instructions, live SRAM,
caller ABI and device-boundary effects, checking input hashes before/after each run.
Only observed private stack frames are excluded from RAM comparisons. Real driver
execution in the edge suite is limited to validation/busy/locked early exits before
MMIO. See the [compatibility follow-up](verification.md#logic-compatibility-follow-up-2026-11-08).
Sanitizer runs appear in historical evidence; ordinary Makefile targets do not
automatically enable ASan/UBSan.

## Enforced and observed patterns

- [Architecture checks](../tests/check_architecture.py) protect portable boundaries and original HEX identity.
- [Build preparation](../firmware/tools/prepare_legacy.py) constrains generated paths, replacement windows, and extension fill.
- [Linker assertions](../firmware/platform/apm32/firmware.ld) protect layout and prohibit new static RAM.
- [Native checks](../tests/check_native.py) compare actual compiled ARM paths, permitted image differences,
  RAM effects, device-call traces, and selected original caller register dependencies.
- Public API preconditions remain part of correctness; do not assume all functions reject every invalid pointer.

## Operational failure boundaries

Storage readiness depends on tick advancing while the probe is busy.
The timeout is elapsed legacy ticks greater than 500, with unsigned subtraction;
the code does not establish wall-clock milliseconds. Read status propagates, while
write/probe errors normalize to 1. Zero-length I/O is intentionally retained.
See [storage contracts](../firmware/include/charge/storage.h).

Caller/platform code owns serialization of channel state updates and parser use.
Emulation intercepts device boundaries; it does not supply electrical behavior,
real IRQ/DMA scheduling, cycle accuracy, or measured stack headroom.
The original scheduler and Boot remain outside the scope of native C migration.

## Acceptance targets

> **TODO(owner):** Define board acceptance criteria and quantitative reliability targets, including startup/upgrade, timing, IRQ concurrency, stack headroom, and external-device behavior.

Current development artifacts are not documented as accepted production releases.
See [recorded gaps](verification.md), [quality evidence](QUALITY_SCORE.md),
and [execution plans](PLANS.md).

[Agent map](../AGENTS.md)
