# Product Sense

## Documented repository purpose

The [project overview](../README.md) and [development guide](../firmware/README.md)
establish two purposes: preserve a reproducible firmware recovery baseline, and provide
maintainable C modules for continued development without discarding unmigrated behavior.

Observed capabilities include serial commands, twelve-channel state, configuration,
timers, external storage, and firmware-update logic. Those observations do not establish
the product's commercial positioning, physical operating envelope, or end-user workflow.

## Owner-confirmed direction

On 2026-11-08 the owner requested a complete Knowledge Store to support future development
and iteration of this project. This establishes the documentation purpose; it does not
supply product users, delivery commitments, or board acceptance criteria.

## Product decisions awaiting the owner

> **TODO(owner):** Define the primary users, deployment context, highest-value scenarios, and measures of product success.

## Present limits

The development image has seven native C replacements. It remains dependent on legacy
assembly and has no recorded board acceptance. Product claims must distinguish this
development state from the byte-identical recovery artifact.

See the [specification index](product-specs/index.md), [quality evidence](QUALITY_SCORE.md),
and [active-plan questions](exec-plans/active/README.md) before prioritizing work.

[Agent map](../AGENTS.md)
