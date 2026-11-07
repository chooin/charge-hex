# Database and Binary Storage Inventory

No database engine, ORM, or database migration framework was found. Relational schema
generation is not applicable. This file instead indexes layouts recoverable from current
headers, the platform bridge, linker script, and existing recovery notes.

Source inspection: 2026-11-08. This is a manually derived inventory, not a generated
claim of complete field semantics or a new persistent format.

## Flash

| Region | Inclusive address range | Evidence |
| --- | --- | --- |
| Boot | 0x08000000–0x08003FFF | [Partition evidence](../../recovery/artifacts/partitions.json) |
| Application | 0x08004000–0x0800F7FF | [Partition evidence](../../recovery/artifacts/partitions.json) |
| Native C extension within App | 0x0800D000–0x0800F7FF | [Current linker](../../firmware/platform/apm32/firmware.ld) |
| Update metadata | 0x0800F800–0x0800FBFF | [Startup notes](../../recovery/notes/startup.md) |
| Configuration page | 0x0800FC00–0x0800FFFF | [Inventory](../../recovery/notes/inventory.md) |

The recovery partition boundaries were selected from observed vectors and data, not
recovered original linker metadata. The current linker preserves the final 2 KiB.

## Caller-owned C layouts

| Type or buffer | Size / shape | Contract source |
| --- | --- | --- |
| ChargeChannel | 52 bytes, 12 channels; size and selected offsets asserted | [channel.h](../../firmware/include/charge/channel.h) |
| Configuration | 120 bytes; dirty flag at byte 118 | [config.h](../../firmware/include/charge/config.h) |
| Parameter payload | 23 bytes, endian flag 1 selects big-endian | [config.h](../../firmware/include/charge/config.h) |
| Channel state | Bitmap plus three packed bytes | [channel.h](../../firmware/include/charge/channel.h) |
| Timer helpers | uint16 values; 93-slot constant, no scheduler implementation | [timer.h](../../firmware/include/charge/timer.h) |
| Serial parser | Three uint8 state fields plus independent 256-byte buffer | [protocol.h](../../firmware/include/charge/protocol.h) |
| Serial output | At most 166 payload bytes / 171 frame bytes; identifier frame 11 bytes | [protocol.h](../../firmware/include/charge/protocol.h) |

Offset-based fields deliberately retain unknown physical units. These RAM/wire layouts
are not proof that every byte is persisted unchanged.

## Platform bindings and external storage

The [bridge](../../firmware/platform/apm32/legacy_bridge.c) binds channel state to
0x200000B8/0x200000DD, channel records to 0x200005E4, configuration to 0x20000854,
TX storage to 0x20000A18, and the I²C driver context to 0x20000B6C.
These addresses belong to the platform layer.

[Storage](../../firmware/src/services/storage.c) uses 16-bit addresses, rejects ranges
crossing 65,536 bytes, and splits writes at 128-byte page boundaries.
The bridge supplies device address 0xA0 and two-byte memory addressing.
The external part's identity is not confirmed; see [update notes](../../recovery/notes/update_protocol.md).
The page size and address space do not prove a specific device model.

The original RX buffer starting at 0x20001024 is not established as a valid 256-byte
allocation for the new parser. See [Design](../DESIGN.md) before changing RX integration.

[Architecture](../../ARCHITECTURE.md) · [Agent map](../../AGENTS.md)
