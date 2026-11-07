# Technical References

## Repository sources of truth

| Topic | Local reference |
| --- | --- |
| Project constraints and evidence hashes | [Root README](../../README.md) |
| Current development workflow | [Firmware guide](../../firmware/README.md) |
| Migration rationale and existing upstream references | [Original architecture record](../architecture.md) |
| Hardware identification and compatible register-layout sources | [Inventory](../../recovery/notes/inventory.md), [startup notes](../../recovery/notes/startup.md) |
| Original function and memory map | [Recovery module map](../../recovery/MODULE_MAP.md) |
| Serial and update behavior | [Protocol notes](../../recovery/notes/protocol.md), [update notes](../../recovery/notes/update_protocol.md) |
| Model instruction/exception limits | [Model review](../../recovery/full_c/review.md) |
| Recovery tool provenance and digests | [Tool source manifest](../../recovery/ghidra/tool_source.json) |
| Host Python versions | [Pinned dependencies](../../requirements-dev.txt) |

## External-reference inventory

These references are already cited by repository documents. Their contents were not
newly fetched or verified for this Knowledge Store; follow the local evidence links
for the exact URLs and historical context.

- Geehy APM32F030x6/x8 datasheet and ST compatible-layout startup/header references:
  [inventory](../../recovery/notes/inventory.md).
- Arm/Keil APM32F030C8 device page and CMSIS-Driver operating model:
  [migration design](../architecture.md). CMSIS-Driver is a design reference, not a vendored implementation.
- Arm Cortex-M0+ guide and shift/carry behavior:
  [model boundary review](../../recovery/full_c/review.md).
- REA/Ghidra recovery tooling:
  [recorded provenance](../../recovery/ghidra/tool_source.json). Recorded versions are not claims about current releases.

No tool-specific llms.txt reference files are currently maintained here.
Add such files only with source URL, version/date, and clear relevance to the project.

[Design index](../design-docs/index.md) · [Agent map](../../AGENTS.md)
