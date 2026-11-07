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
extern uint32_t fw_08005fb8(void *, uint16_t, uint16_t, uint16_t,
                          uint8_t *, uint16_t, uint32_t);
extern uint32_t fw_0800610c(void *, uint16_t, uint16_t, uint16_t,
                          const uint8_t *, uint16_t, uint32_t);
/* Zero-length master transmit, NOT a four-argument IsDeviceReady API. */
extern uint32_t fw_08005ea8(void *, uint16_t, const uint8_t *, uint16_t, uint32_t);
extern uint32_t fw_08005d54(void);

void charge_legacy_set_channel_impl(uint8_t channel, uint8_t enabled)
{
    charge_channel_set_state((volatile uint32_t *)0x200000b8u,
                            (volatile uint8_t *)0x200000ddu, channel, enabled);
}

void charge_legacy_clear_channel_impl(uint8_t channel)
{
    /* Original callers establish channel bounds; preserve the original ABI. */
    charge_channel_clear_accounting(&((volatile ChargeChannel *)0x200005e4u)[channel]);
}

void charge_legacy_apply_config(const uint8_t *payload, uint8_t big_endian)
{
    charge_config_apply_payload((uint8_t *)0x20000854u, payload, big_endian);
}

void charge_legacy_send_frame(uint8_t command, uint8_t length, uint8_t subcommand,
                              const uint8_t *payload, uint8_t prefix)
{
    uint8_t *out = (uint8_t *)0x20000a18u;
    uint16_t count = charge_serial_build_frame(out, 171, command, length,
                                               subcommand, payload, prefix);
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
uint32_t charge_legacy_storage_read_impl(uint16_t address, uint8_t *data, uint16_t size)
{
    return charge_storage_read(&storage, address, data, size);
}
uint32_t charge_legacy_storage_write(uint16_t address, const uint8_t *data, uint16_t size)
{
    return charge_storage_write(&storage, address, data, size);
}
uint32_t charge_legacy_storage_wait_ready_impl(void)
{
    return charge_storage_wait_ready(&storage);
}
