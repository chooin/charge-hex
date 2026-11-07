# Architecture

Source inspection: 2026-11-08. This map describes the current working tree, including
the development layer described in the existing [migration design](docs/architecture.md).
It does not assert that the working tree equals the last committed recovery baseline.

The [visual architecture overview](docs/diagrams/charge-architecture.html) provides
two Chinese diagrams: current runtime integration, and development-build/recovery
evidence boundaries. Open the self-contained HTML in a browser; it also includes
the seven native replacement entries and source references.

The [board interaction overview](docs/diagrams/charge-board-interactions.html)
maps runtime communication, inputs, GPIO outputs, display, and external storage,
with a companion command-to-output sequence. Unconfirmed device identities and
connector mappings remain explicit.

## System and evidence boundaries

The repository maintains an immutable original Intel HEX image, a reproducible recovery
project, and an incremental C firmware project. Existing [inventory evidence](recovery/notes/inventory.md)
identifies the board as Geehy APM32F030C8T6, Cortex-M0+, with 64 KiB Flash and 8 KiB SRAM
as summarized by the [existing architecture record](docs/architecture.md).
The legacy application uses a bare-metal main loop and interrupts.

| Layer | Role | Boundary |
| --- | --- | --- |
| [Original HEX](stm32_fw.hex) and [board photo](主板.png) | Original supplied evidence | HEX is immutable; see [README](README.md) |
| [recovery/](recovery/README.md) | Assembly reproduction, CPU model, decompilation, notes | Evidence and verification oracle |
| [firmware/include/charge/](firmware/include/charge/) | Public C contracts and data types | Caller-owned state and explicit preconditions |
| [firmware/src/domain/](firmware/src/domain/) | Channel, configuration, timer rules | No hardware, protocol, or storage dependencies |
| [firmware/src/protocol/](firmware/src/protocol/) | Serial byte semantics | Returns events/frames; no UART side effects |
| [firmware/src/services/](firmware/src/services/) | Storage paging and CRC | Storage uses synchronous callback ports |
| [firmware/platform/apm32/](firmware/platform/apm32/) | Original addresses, drivers, ABI, linker layout | Owns board-specific integration |
| [tests/](tests/) | Host, differential, native, architecture checks | Scoped behavioral evidence, not hardware certification |

Dependencies flow from original entry points through platform adapters into portable C.
Storage callbacks return to the platform's original I²C and tick routines.
No browser UI, database, HTTP server, RTOS implementation, or vendor SDK integration
is present in the inspected development layer.

## Portable modules

| Module | Contract | Current integration |
| --- | --- | --- |
| [serial.c](firmware/src/protocol/serial.c) | Event parser, block XOR, frame and identifier builders | Frame send integrated; original RX and other paths remain |
| [config.c](firmware/src/domain/config.c) | 23-byte payload into 120-byte configuration | Integrated |
| [channel.c](firmware/src/domain/channel.c) | 12 channels, 52-byte records, bitmap and packed state | Set-state and accounting-clear integrated |
| [timer.c](firmware/src/domain/timer.c) | Legacy delta and subtraction rules; 93-slot constant | Original scheduler remains |
| [storage.c](firmware/src/services/storage.c) | Range checks, 128-byte pages, readiness polling | Read, wait, and write integrated |
| [crc16.c](firmware/src/services/crc16.c) | Recovered recurrence and two-byte augmentation | Original Boot CRC remains |

The public headers are authoritative for caller preconditions. Not every API performs
NULL checks. Unknown physical units retain neutral names rather than guessed meanings.

## Native migration

[prepare_legacy.py](firmware/tools/prepare_legacy.py) reads the recovery assembly and
original HEX, verifies the HEX identity and extension fill, and writes only under
firmware/build/. It replaces the first 16 bytes of seven original entries:

| Original address | Replacement role |
| --- | --- |
| 0x08007498 | Storage read |
| 0x080074C4 | Storage readiness |
| 0x080074FC | Storage write |
| 0x08009E14 | Channel accounting clear |
| 0x0800BCD8 | Configuration payload |
| 0x0800C7C4 | Serial frame send |
| 0x0800C85C | Channel state |

Dedicated [shims](firmware/platform/apm32/abi_shims.S) preserve additional registers
required by real legacy callers, including clear-channel r3 and storage-read r1/r2.
The original startup, main loop, complex business handlers, IRQ/DMA, most drivers,
and Boot continue to execute legacy assembly.

## Memory and outputs

| Region | Inclusive addresses | Current role |
| --- | --- | --- |
| Boot | 0x08000000–0x08003FFF | Preserved original Boot |
| App | 0x08004000–0x0800F7FF | Original application plus extension |
| C extension within App | 0x0800D000–0x0800F7FF | 10 KiB reserved for linked C/shims |
| Metadata | 0x0800F800–0x0800FBFF | Preserved persistent bytes |
| Configuration | 0x0800FC00–0x0800FFFF | Preserved persistent bytes |

The [linker](firmware/platform/apm32/firmware.ld) rejects new .data/.bss because legacy
startup does not initialize them. The adapter requires the original extension range
to contain explicit FF fill. Static checks do not settle all dynamic target/self-read risks.

[firmware/Makefile](firmware/Makefile) produces a host library and charge
ELF/BIN/HEX outputs representing a 64 KiB Flash image. That development image intentionally differs from the original.
Only the separate [assembly recovery](recovery/full_assembly/README.md) carries the
recorded byte-identical claim. No upgrade-specific app.bin or flashing target is supplied.

## Reading next

- [Design](docs/DESIGN.md): compatibility and integration constraints.
- [Storage inventory](docs/generated/db-schema.md): binary state, not relational tables.
- [Reliability](docs/RELIABILITY.md): verification commands and hardware limits.
- [Technical debt](docs/exec-plans/tech-debt-tracker.md): remaining migration work.
- [Agent map](AGENTS.md): entry point for subsequent work.
