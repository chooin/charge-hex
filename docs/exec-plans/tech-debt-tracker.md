# Technical Debt Tracker

Source-derived inventory, reviewed 2026-11-08. These are observed gaps, not an ordered
roadmap or newly reproduced failures. A scoped source/document search found no actionable
TODO/FIXME markers; prose evidence below supplies the work items.

| ID | Gap and impact | Evidence | Current status |
| --- | --- | --- | --- |
| TD-01 | Historical application.c uses four arguments for the five-argument I²C ready probe | [Translation](../../recovery/reconstructed/application.c), [correct current bridge](../../firmware/platform/apm32/legacy_bridge.c) | Open in historical translation; current development adapter is correct |
| TD-02 | Main loop, complex business handlers, Boot, IRQ/DMA, and most drivers remain assembly | [Migration design](../architecture.md), [entry map](../../firmware/tools/prepare_legacy.py) | Partial C migration; legacy behavior retained |
| TD-03 | Portable RX parser cannot be substituted without buffer-boundary and callback/IRQ timing work | [Protocol contract](../../firmware/include/charge/protocol.h), [development guide](../../firmware/README.md) | New API exists; original RX retained |
| TD-04 | Physical timing, concurrency, stack headroom, external devices, startup, and upgrade lack board acceptance | [Verification](../verification.md) | Unverified |
| TD-05 | Unknown physical units, record meanings, wiring, and device identities constrain further migration | [Recovery map](../../recovery/MODULE_MAP.md), [application notes](../../recovery/notes/application.md) | Preserve neutral field names |
| TD-06 | No upgrade-only package includes the new extension and demonstrates Boot transfer/commit behavior | [Migration design](../architecture.md) | No development app.bin produced |
| TD-07 | Historical upgrade notes describe odd-length truncation and incomplete commit/error handling | [Update protocol](../../recovery/notes/update_protocol.md) | Retained original observations; not a newly tested vulnerability |
| TD-08 | Main-loop dynamic coverage excludes some button waits, timing, and business conditions | [Main-loop notes](../../recovery/notes/application_main.md) | Partial scenarios |
| TD-09 | Decompiler warnings and indirect-control-flow uncertainty remain | [Decompiler guide](../../recovery/decompiled/README.md), [model review](../../recovery/full_c/review.md) | Classified coverage is not complete reachability proof |
| TD-10 | Recovery model differential library build uses macOS-specific dynamic-library flags | [Model guide](../../recovery/full_c/README.md) | Cross-platform verification setup not established |

> **TODO(owner):** Assign debt owners, priorities, acceptance criteria, and target dates; distinguish planned work from acknowledged compatibility limitations.

Keep evidence and status current as items change. Link implementation plans from
[active plans](active/README.md), and retain residual risks when archiving completion.

[Agent map](../../AGENTS.md)
