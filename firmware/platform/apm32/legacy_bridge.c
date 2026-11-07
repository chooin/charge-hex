/* Transitional board adapter. Only this layer knows the recovered RAM/ABI.
 * Existing startup, IRQs, main, and device drivers remain in legacy assembly.
 * No new static RAM: the original startup cannot initialize new .data/.bss.
 */
#include "charge/channel.h"
#include "charge/config.h"
#include "charge/protocol.h"
#include "charge/storage.h"
#include <stdint.h>

extern void fw_0800947c(const uint8_t *, uint16_t);
extern uint32_t charge_legacy_read_byte(uint32_t address);
/* These are raw register/stack entry contracts. The original wrappers pass
 * full-width address/size values; narrowing here changes exceptional paths. */
extern uint32_t fw_08005fb8(void *, uint32_t, uint32_t, uint32_t,
                          uint8_t *, uint32_t, uint32_t);
extern uint32_t fw_0800610c(void *, uint32_t, uint32_t, uint32_t,
                          const uint8_t *, uint32_t, uint32_t);
/* Zero-length master transmit, NOT a four-argument IsDeviceReady API. */
extern uint32_t fw_08005ea8(void *, uint16_t, const uint8_t *, uint16_t, uint32_t);
extern uint32_t fw_08005d54(void);

void charge_legacy_set_channel_impl(uint32_t channel, uint32_t enabled)
{
    /* The original entry normalizes the channel to eight bits itself, while
     * testing the full enable register. A narrow C parameter alone assumes
     * that its caller already extended/truncated the value; legacy code has
     * no such entry guarantee. Preserve both machine-level operations here.
     */
    charge_channel_set_state((volatile uint32_t *)0x200000b8u,
                            (volatile uint8_t *)0x200000ddu,
                            (uint8_t)channel, enabled != 0);
}

void charge_legacy_clear_channel_impl(uint32_t channel)
{
    /* Original callers establish channel bounds; preserve the original ABI. */
    charge_channel_clear_accounting((volatile ChargeChannel *)(uintptr_t)
                                    (0x200005e4u + channel * 52u));
}

void charge_legacy_apply_config(const uint8_t *payload, uint32_t big_endian)
{
    charge_config_apply_payload((uint8_t *)0x20000854u, payload, big_endian == 1);
}

void charge_legacy_send_frame(uint32_t command, uint32_t length, uint32_t subcommand,
                              const uint8_t *payload, uint32_t prefix)
{
    if (length > 166u) return;
    uint8_t *out = (uint8_t *)0x20000a18u;
    if (payload == 0 && length != 0) {
        /* The machine entry accepts address zero as a mapped byte source.
         * Preserve its read order without expressing a C NULL dereference. */
        volatile uint8_t *wire = out;
        wire[0] = (uint8_t)prefix;
        wire[1] = (uint8_t)(length + 3u);
        wire[2] = (uint8_t)command;
        wire[3] = (uint8_t)subcommand;
        for (uint32_t i = 0; i < length; ++i)
            wire[i + 4u] = (uint8_t)charge_legacy_read_byte(i);
        wire[length + 4u] = 0;
        for (uint32_t i = 1; i < length + 4u; ++i)
            wire[length + 4u] ^= wire[i];
        fw_0800947c(out, (uint16_t)(length + 5u));
        return;
    }
    uint16_t count = charge_serial_build_frame(out, 171, (uint8_t)command,
        (uint8_t)length, (uint8_t)subcommand, payload, (uint8_t)prefix);
    if (count) fw_0800947c(out, count);
}

static uint32_t storage_read(void *context, uint16_t address, uint8_t *data,
                             uint16_t size, uint32_t timeout)
{
    return fw_08005fb8(context, 0xa0, address, 2, data, size, timeout);
}
static uint32_t storage_write(void *context, uint16_t address, const uint8_t *data,
                              uint16_t size, uint32_t timeout)
{
    return fw_0800610c(context, 0xa0, address, 2, data, size, timeout);
}
static uint32_t storage_probe(void *context, uint32_t timeout)
{
    return fw_08005ea8(context, 0xa0, 0, 0, timeout);
}
static uint32_t storage_tick(void *context)
{
    (void)context;
    return fw_08005d54();
}
static const ChargeStorage storage = {
    .context = (void *)0x20000b6cu, .read = storage_read, .write = storage_write,
    .probe = storage_probe, .tick = storage_tick
};
uint32_t charge_legacy_storage_read_impl(uint32_t address, uint8_t *data, uint32_t size)
{
    if ((uint32_t)(0x10000u - address) < size) return 1;
    if (address <= UINT16_MAX && size <= UINT16_MAX && (data != 0 || size == 0))
        return charge_storage_read(&storage, (uint16_t)address, data, (uint16_t)size);
    /* Preserve original driver validation, error-state writes and raw status,
     * including NULL transfers that the portable API deliberately rejects. */
    return fw_08005fb8(storage.context, 0xa0, address, 2, data, size, 1000);
}

static uint32_t legacy_write_chunk(uint32_t address, uint32_t data, uint32_t size)
{
    if (fw_0800610c(storage.context, 0xa0, address, 2,
                   (const uint8_t *)(uintptr_t)data, size, 500) != 0) return 1;
    return charge_storage_wait_ready(&storage);
}

uint32_t charge_legacy_storage_write(uint32_t address, const uint8_t *data, uint32_t size)
{
    if ((uint32_t)(0x10000u - address) < size) return 1;
    if (address <= UINT16_MAX && size <= UINT16_MAX && (data != 0 || size == 0))
        return charge_storage_write(&storage, (uint16_t)address, data, (uint16_t)size);

    /* Exceptional register inputs follow 0800750E..080075D2 exactly. The
     * signed-division adjustment precedes explicit 16-bit page/tail masks;
     * this is not equivalent to truncating size on entry. Integer pointer
     * arithmetic also preserves the original 32-bit wrap without C pointer
     * arithmetic on NULL or outside an object. The portable API is unchanged. */
    uint32_t cursor = (uint32_t)(uintptr_t)data;
    uint32_t first = 128u - (address & 127u);
    if (first >= size) return legacy_write_chunk(address, cursor, size);
    uint32_t remaining = size - first;
    uint32_t adjusted = remaining + ((remaining & 0x80000000u) ? 127u : 0u);
    uint32_t pages = (adjusted >> 7) & 0xffffu;
    uint32_t tail = (remaining - (adjusted & ~127u)) & 0xffffu;
    if (legacy_write_chunk(address, cursor, first) != 0) return 1;
    address = (address + first) & 0xffffu;
    cursor += first;
    while (pages != 0) {
        if (legacy_write_chunk(address, cursor, 128) != 0) return 1;
        address = (address + 128u) & 0xffffu;
        cursor += 128;
        --pages;
    }
    return tail == 0 ? 0 : legacy_write_chunk(address, cursor, tail);
}
uint32_t charge_legacy_storage_wait_ready_impl(void)
{
    return charge_storage_wait_ready(&storage);
}
