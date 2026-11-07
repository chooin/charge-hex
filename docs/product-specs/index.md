# Product Specification Index

This repository contains firmware and recovery evidence, not an owner-approved
end-user requirements set. The following index captures observed capabilities only.

| Capability | Available evidence | Specification status |
| --- | --- | --- |
| Serial framing and parameter payload processing | [Protocol notes](../../recovery/notes/protocol.md), [public contracts](../../firmware/include/charge/) | Recovered behavior; partly integrated C |
| Twelve-channel state and accounting records | [Channel contract](../../firmware/include/charge/channel.h), [business notes](../../recovery/notes/business_handlers.md) | Record layout known; some business meanings remain unknown |
| Timing and application coordination | [Main-loop notes](../../recovery/notes/application_main.md) | Main loop remains legacy |
| Paged external storage and update CRC | [Storage contract](../../firmware/include/charge/storage.h), [update notes](../../recovery/notes/update_protocol.md) | Storage integrated; Boot/update path retained |
| Reproducible recovery and incremental development | [Project overview](../../README.md), [development guide](../../firmware/README.md) | Established repository workflow |

> **TODO(owner):** Confirm target users, operational scenarios, expected outcomes, and acceptance criteria for product specifications.

A new specification should distinguish observed compatibility requirements from intended
behavior changes, state unknowns, and link its implementation and validation evidence.
Do not infer billing rules, electrical limits, or release readiness from function names.

[Product sense](../PRODUCT_SENSE.md) · [Plans](../PLANS.md) · [Agent map](../../AGENTS.md)
