# Design Documents

Unless separately dated, status means source consistency at the 2026-11-08 documentation review, not a fresh
build, test run, hardware check, or owner approval.

| Document | Scope | Status |
| --- | --- | --- |
| [Architecture](../../ARCHITECTURE.md) | Current layers, memory, migration boundary | Cross-checked against source |
| [Design patterns](../DESIGN.md) | State, callbacks, compatibility, ABI | Cross-checked against headers and adapters |
| [Core beliefs](core-beliefs.md) | Existing repository constraints | Documented constraints; additional owner policy pending |
| [Migration contracts and verification runs](migration-contracts.md) | Checked entry registration and isolated evidence | 2026-11-13 implementation; see execution plan for verification |
| [Original migration design](../architecture.md) | Chinese rationale and migration decisions | Existing dated record, preserved |
| [Verification record](../verification.md) | 2026-11-07 acceptance evidence | Historical results; not rerun |
| [Recovery map](../../recovery/MODULE_MAP.md) | Original functions and evidence | Historical analysis; partial C migration now exists |

Keep original records intact. New decisions should state source evidence, alternatives,
behavioral consequences, and validation scope. Link implementation work through
[execution plans](../PLANS.md) and expose persistent gaps in [technical debt](../exec-plans/tech-debt-tracker.md).

[Agent map](../../AGENTS.md)
