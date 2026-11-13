# Migration contracts and isolated verification runs

Status: implementation and verification complete
Owner: repository owner, implementation delegated to Codex
Date: 2026-11-13

## Scope

Implement the first maintenance phase: executable contracts for the seven existing
native entries, isolated verification outputs, and recorded build/tool identity.
Keep the original HEX, recovery evidence, runtime C/assembly and linker behavior
unchanged. Application-use-case and IRQ/scheduler migration remain future work.

## Acceptance

- Missing or inconsistent native-entry ABI, caller or test contracts are rejected.
- Verification commands write fresh run outputs, never tracked historical reports.
- A run records inputs, effective build configuration, tools, steps and output hashes;
  failure, interruption and changed inputs cannot appear as a passing full run.
- Recovery audit consumes the model verification from the same run.
- `make verify` and `make verify-recovery` pass without tracked-file changes.
- Native BIN and recovered BIN remain byte-identical to the pre-change builds.

## Work

- [x] Migration manifest, build validation and negative regressions.
- [x] Report routing and run orchestration.
- [x] Documentation and complete verification.

## Verification evidence

Based on master `015af384dc6674a11ffc6b9dcf864157cf0181c4` plus this implementation.
Final command: `python3 recovery/tools/run_verification.py all`.
Local run: `20261113T014406Z-x3cr2c3_` under `recovery/build/verification/`.
Both suites passed; the run reports no changed build/check inputs.

- 18 migration-contract regressions, 12 run-acceptance regressions and 11 recovery
  workflow regressions passed. The run tests also execute from the standalone
  recovery suite, without requiring a live REA/Ghidra provider.
- Native differential suites: 1,642 + 5,884 + 20,376 paired cases.
- Recovery standalone byte rebuild, artifact checks, selected behavior differences,
  42,138 single-instruction and 1,354 whole-function C-model comparisons, and
  3,584 model-boundary comparisons passed.
- Native BIN SHA-256 remains
  `654e16eeb7b19c2b95835c656eefc09b640eaac5fd986abdb30694befdb87611`.
- Recovery BIN SHA-256 remains
  `3016dafb97375b22cdb49f1ed41b05c7f1aa940d58c5ce42c2fdbe682245a144`.
- Original HEX and committed historical reports remained unchanged.

Independent review identified and resolved missing final artifact identity checks,
root-log misclassification as input, and incomplete tool/interpreter provenance.
The final review found no blocking defects. Board execution was not performed.

## Delivery and follow-up

The owner authorized a PR and merge to master after verification; GitHub is the
authority for delivery status. Later phases (application use cases, state ownership,
IRQ/scheduler migration) are not implemented or accepted by this phase.
