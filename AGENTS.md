# Agent Map

Charge is a firmware recovery baseline and incremental C development project for the
Geehy APM32F030C8T6 board identified in the existing recovery evidence.

## Start here

- Read the [project overview](README.md) for the original evidence protection rules.
- Use [firmware/](firmware/README.md) for current development.
- Use [Architecture](ARCHITECTURE.md) for module boundaries and migration status.
- Use [Design](docs/DESIGN.md) before changing an integration boundary.
- Use [Reliability](docs/RELIABILITY.md) to select verification for a change.
- Treat [recorded verification](docs/verification.md) as dated evidence, not a new run.

## Non-negotiable repository constraints

- Never modify, delete, reformat, or overwrite the root stm32_fw.hex.
- Preserve its exact text bytes, record order, case, and line endings.
- Perform transformations on separate copies; keep outputs in build directories.
- The expected original HEX SHA-256 is:
  22b4c0a573576b2f0f9ea93fc3459f22163f3c5305875a245f3ea82c4a373ccf
- If its identity differs, stop using it as the oracle; do not rewrite expected hashes.
- See [README protection rules](README.md) for the full recovery procedure.
- Keep recovery evidence distinct from current development and generated artifacts.
- Do not claim hardware acceptance from host or emulation results.

## Find the implementation

| Concern | Start |
| --- | --- |
| Public contracts and caller-owned state | [Headers](firmware/include/charge/) |
| Channel, configuration, and timer rules | [Domain](firmware/src/domain/) |
| Serial frames, checksums, parser events | [Protocol](firmware/src/protocol/serial.c) |
| Paged storage and update CRC | [Services](firmware/src/services/) |
| Absolute addresses and original driver calls | [Platform bridge](firmware/platform/apm32/legacy_bridge.c) |
| Nonstandard register contracts | [ABI shims](firmware/platform/apm32/abi_shims.S) |
| Flash layout and no-new-static-RAM check | [Linker script](firmware/platform/apm32/firmware.ld) |
| Seven native entry replacements | [Build adapter](firmware/tools/prepare_legacy.py) |
| Entry/ABI/state/caller/test registration | [Migration contract](firmware/platform/apm32/migration.json) |
| Fresh verification runs and provenance | [Run coordinator](recovery/tools/run_verification.py) |
| Host, differential, and native checks | [Tests](tests/) |
| Original-function reading map | [Recovery map](recovery/MODULE_MAP.md) |

## Evidence layers

- [Full assembly](recovery/full_assembly/README.md): independent, byte-identical recovery.
- [Full C model](recovery/full_c/README.md): host instruction-semantics model.
- [Decompiler output](recovery/decompiled/README.md): analysis with warnings retained.
- [Readable reconstructions](recovery/reconstructed/): historical translations with known gaps.
- [Current firmware](firmware/README.md): partial C migration using legacy assembly.
- These layers have different verification claims; see [quality evidence](docs/QUALITY_SCORE.md).

## Working conventions

- Keep hardware addresses, original ABI, and device calls in the platform layer.
- Keep portable modules independent of platform/recovery imports and heap allocation.
- State belongs to callers; interrupt serialization is a caller/platform responsibility.
- Preserve unknown field names and units until supported by evidence.
- Consult the public header for each API's pointer, size, aliasing, and lifetime contract.
- Do not wire the portable RX parser into the original buffer without resolving its allocation and timing constraints.
- Preserve original entry behavior and verify actual callers when adding a native replacement.
- Keep raw native register contracts and legacy error side effects in the adapter; portable API guards are separate contracts.
- See [core beliefs](docs/design-docs/core-beliefs.md) for sources of these constraints.

## Command map

Run from the repository root; details and dependencies are in [Reliability](docs/RELIABILITY.md).

| Command | Purpose |
| --- | --- |
| make host | Portable C library |
| make native | Transitional ARM ELF/BIN/HEX |
| make test | Host tests, architecture checks, original-Thumb differential tests |
| make verify | Build, tests, and native integration checks |
| make verify-recovery | Independent recovery verification |

Verification scripts use assertions: do not run them with Python optimization enabled.
`make verify` and `make verify-recovery` create isolated reports and image copies in
`recovery/build/verification/<run-id>/`; inspect that run's `run.json`, not a historical PASS.
Build and verification commands are documented here, not automatically run by documentation work.

## Knowledge Store

- [Design index](docs/design-docs/index.md) — decisions and evidence status
- [Core beliefs](docs/design-docs/core-beliefs.md) — established constraints and open policy
- [Design patterns](docs/DESIGN.md) — state, ports, compatibility, and ABI
- [Plans](docs/PLANS.md) — execution-plan format and lifecycle
- [Active plans](docs/exec-plans/active/README.md) — owner-selected work
- [Completed plans](docs/exec-plans/completed/README.md) — archived execution evidence
- [Technical debt](docs/exec-plans/tech-debt-tracker.md) — known gaps and source pointers
- [Storage/schema inventory](docs/generated/db-schema.md) — binary layouts; no database
- [Product specification index](docs/product-specs/index.md) — observed capabilities
- [Product sense](docs/PRODUCT_SENSE.md) — documented purpose and owner questions
- [Quality evidence](docs/QUALITY_SCORE.md) — scoped evidence and unmeasured areas
- [Reliability](docs/RELIABILITY.md) — checks, failure boundaries, and acceptance gaps
- [Security](docs/SECURITY.md) — established integrity rules and missing policy
- [References](docs/references/index.md) — local evidence and tool references
- [API Conventions](docs/API.md) — response shape, pagination, errors, versioning (GitHub REST style)

No frontend or HTTP backend was found. The API conventions file is a reserved placeholder.
CLAUDE.md is a relative symlink to this canonical map.
