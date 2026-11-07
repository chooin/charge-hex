# Security

This document records established repository integrity constraints and missing owner
policy. It is not a security audit, vulnerability assessment, or certification.

## Existing constraints and evidence

- Preserve the original HEX exactly, following [README](../README.md).
  Never replace the oracle with a reconstruction or change expected hashes to hide a mismatch.
- Keep output artifacts separate from supplied evidence; the current build adapter
  restricts generated compatibility source to firmware/build/.
- The new serial API preserves compatibility quirks and has not replaced original RX.
  Its bounded API checks do not establish whole-protocol hardening.
- Existing [update notes](../recovery/notes/update_protocol.md) describe behavior and
  limitations of the original update flow. They do not demonstrate secure update
  authentication, rollback protection, or end-to-end validation of the new image.
- Physical board operation and production readiness remain unverified in the
  [acceptance record](verification.md).

## Policy awaiting the owner

> **TODO(owner):** Define the security owner/reporting channel, threat model, compliance obligations, and firmware release/update security requirements.

Do not infer a disclosure process, legal certification, access-control model, or
cryptographic guarantee from absent documentation. Track implementation work with
[plans](PLANS.md) and preserve the evidence scope in [quality records](QUALITY_SCORE.md).

[Agent map](../AGENTS.md)
