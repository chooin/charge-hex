#include "charge/config.h"
#include <stddef.h>

static uint16_t read_payload_u16(const uint8_t *p, uint8_t big_endian)
{
    return big_endian == 1 ? (uint16_t)((uint16_t)p[0] << 8 | p[1])
                          : (uint16_t)((uint16_t)p[1] << 8 | p[0]);
}

static uint16_t read_config_u16(const uint8_t *config, unsigned offset)
{
    return (uint16_t)((uint16_t)config[offset + 1] << 8 | config[offset]);
}

static void write_config_u16(uint8_t *config, unsigned offset, uint16_t value)
{
    config[offset] = (uint8_t)value;
    config[offset + 1] = (uint8_t)(value >> 8);
}

/* Behavioral source: 0x0800BCD8 and endian helper 0x0800A6A0. */
void charge_config_apply_payload(uint8_t config[CHARGE_CONFIG_SIZE],
    const uint8_t payload[CHARGE_PARAMETER_PAYLOAD_SIZE], uint8_t big_endian)
{
    if (payload == NULL) return;
    write_config_u16(config, 2, read_payload_u16(payload, big_endian));
    write_config_u16(config, 4, read_payload_u16(payload + 2, big_endian));
    write_config_u16(config, 8, payload[4]);
    write_config_u16(config, 10, payload[5]);
    write_config_u16(config, 6, payload[6]);
    write_config_u16(config, 12, read_payload_u16(payload + 7, big_endian));
    write_config_u16(config, 14, read_payload_u16(payload + 9, big_endian));
    write_config_u16(config, 16, read_payload_u16(payload + 11, big_endian));
    write_config_u16(config, 18, read_payload_u16(payload + 13, big_endian));
    for (unsigned i = 0; i < 6; ++i)
        write_config_u16(config, 20 + 2 * i, payload[15 + i]);
    write_config_u16(config, 32, (uint16_t)(payload[21] * 60u));
    write_config_u16(config, 34, payload[22]);
    uint16_t limit = read_config_u16(config, 42);
    if (read_config_u16(config, 2) > limit) write_config_u16(config, 2, 240);
    if (read_config_u16(config, 4) > limit) write_config_u16(config, 4, 240);
    if (read_config_u16(config, 6) > 250) write_config_u16(config, 6, 10);
    for (unsigned offset = 12; offset <= 18; offset += 2)
        if (read_config_u16(config, offset) > 2500)
            write_config_u16(config, offset, 2500);
    config[118] = 1;
}
