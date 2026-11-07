# Execution Planning

The owner confirmed that this Knowledge Store should support future development and
iteration of the current project (2026-11-08). No specific migration sequence, assigned
owner, or delivery date was supplied.

## Plan lifecycle

1. Start from the [architecture](../ARCHITECTURE.md), [specifications](product-specs/index.md),
   and [debt tracker](exec-plans/tech-debt-tracker.md).
2. Place selected work in [active plans](exec-plans/active/README.md); state observed
   compatibility contracts separately from intended behavior changes.
3. Record dated progress, decisions, source evidence, and validation results.
4. Move a completed plan to [completed plans](exec-plans/completed/README.md) with
   acceptance evidence and residual gaps; update relevant knowledge links.

This is a lightweight documentation workflow, not a newly introduced CI system or
an assertion that any listed debt is already scheduled.

## Plan template

    # <Concrete change>
    Status: proposed | active | completed
    Owner: <confirmed owner>
    Date: <YYYY-MM-DD>

    ## Problem and desired behavior
    <Current observable behavior and intended outcome.>

    ## Scope and constraints
    <Affected modules, immutable evidence, compatibility contracts, unknowns.>

    ## Implementation steps
    - [ ] <A bounded, reviewable step linked to source paths.>

    ## Validation and acceptance
    <Applicable commands, input domains, hardware requirements, success evidence.>

    ## Progress log
    <Date, completed step, evidence, remaining work.>

    ## Decision log
    <Date, alternatives, decision, evidence and consequences.>

    ## Completion and follow-up
    <Acceptance result, known limitations, debt links.>

A new native replacement plan should identify the original entry and callers, establish
register and memory contracts, select differential scenarios, and distinguish emulator
acceptance from board acceptance. See [Reliability](RELIABILITY.md).

[Agent map](../AGENTS.md)
