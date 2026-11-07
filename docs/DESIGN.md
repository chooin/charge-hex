# Design Decisions and Patterns

This is an English navigation and source summary of the existing
[migration decision record](architecture.md). The original record remains intact.

## Incremental replacement

The chosen design combines portable C modules, small explicit interfaces, and the
existing full-image assembly implementation. It enables routine module development
while preserving functions that have not been migrated. A whole-firmware C rewrite
is not complete; the [architecture map](../ARCHITECTURE.md) lists the seven replaced entries.

The build adapter derives compatibility assembly rather than maintaining a second
hand-edited copy. Replacement code lives in the verified FF extension area.
The linker prevents overflow and rejects new initialized/uninitialized static RAM.

## State and effects

- Domain code operates on caller-owned memory; there is no hidden mutable global state in portable modules.
- Channel record size and selected offsets have compile-time assertions.
- Storage supplies read, write, probe, and tick callbacks; board addressing belongs to the adapter.
- Serial functions construct bytes or return events; transport and command dispatch belong to callers.
- Interrupt serialization is explicit caller/platform work. Volatile accesses do not make related writes atomic.
- The adapter's constant storage port descriptor is distinct from writable static state.

See [headers](../firmware/include/charge/) and [binary layouts](generated/db-schema.md).

## Compatibility is scoped

The parser preserves 8-bit index wrapping and the absence of mode-1 dispatch.
It requires a separate 256-byte buffer, borrows it for returned events, and resets
its index before returning an event. Its timing differs from the original callback.
The original MCU buffer must not be assumed to satisfy this new contract; RX is not migrated.

Only endian flag value 1 selects big-endian configuration decoding. Timer wrap/backward
samples advance one tick; the platform defines tick duration. Storage retains zero-length
I/O and specific error propagation. Consult each header instead of assuming uniform guards.

The platform probe uses the original five-argument zero-length transmit call.
The known four-argument call in historical application.c remains a recovery debt,
not the implementation used by current storage services.

## ABI and acceptance

Legacy callers can depend on more than standard AAPCS preservation rules.
Dedicated assembly shims and actual-caller tests protect observed dependencies.
A changed implementation can still alter stack use, byte-write granularity, IRQ
interleavings, or electrical timing; those require board evidence.

See [Reliability](RELIABILITY.md), [technical debt](exec-plans/tech-debt-tracker.md),
and [core beliefs](design-docs/core-beliefs.md) for remaining work and owner policy.
