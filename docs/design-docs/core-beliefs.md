# Core Beliefs and Constraints

## Established by repository evidence

These are existing rules from [README](../../README.md), the
[development guide](../../firmware/README.md), and the [migration design](../architecture.md),
not newly inferred organizational policy.

1. Preserve the original HEX exactly; it is the independent recovery oracle.
2. Separate readable recovery evidence, generated models, and current development code.
3. Preserve observed business behavior while migrating bounded functionality.
4. Keep rules portable, state caller-owned, and hardware side effects behind explicit ports.
5. Keep unknown fields and units explicit; names do not prove physical meaning.
6. Verify original caller register dependencies when replacing legacy entry points.
7. Distinguish byte identity, sampled semantic agreement, native integration, and board acceptance.
8. Keep generated compatibility code in the build directory and retain its source evidence.

## Owner policy

> **TODO(owner):** Confirm any additional engineering principles, tradeoffs, and non-negotiable product constraints beyond the existing repository rules.

## Agent documentation practice

Use the [agent map](../../AGENTS.md) to locate detailed evidence. When a claim changes,
update its owning document and relevant links. Preserve dated verification records;
do not silently turn old results into claims about new code.

[Design](../DESIGN.md) · [Design index](index.md)
