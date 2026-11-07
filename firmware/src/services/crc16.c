#include "charge/crc16.h"
uint16_t charge_crc16_step(uint16_t previous, uint8_t byte)
{
    uint32_t crc = previous;
    uint32_t input = (uint32_t)byte + 0x100u;
    do {
        crc <<= 1;
        input <<= 1;
        if ((input & 0x100u) != 0) ++crc;
        if ((crc & 0x10000u) != 0) crc ^= 0x1021u;
    } while ((input & 0x10000u) == 0);
    return (uint16_t)crc;
}
uint16_t charge_crc16(const uint8_t *data, uint32_t length)
{
    uint16_t crc = 0;
    for (uint32_t i = 0; i < length; ++i)
        crc = charge_crc16_step(crc, data[i]);
    crc = charge_crc16_step(crc, 0);
    return charge_crc16_step(crc, 0);
}
