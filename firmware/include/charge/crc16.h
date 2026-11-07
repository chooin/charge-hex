#ifndef CHARGE_CRC16_H
#define CHARGE_CRC16_H
#include <stdint.h>
/* Original bit recurrence. It is augmented with two zero bytes by charge_crc16,
 * which produces CRC16/XMODEM (init=0, polynomial=0x1021, xorout=0). */
uint16_t charge_crc16_step(uint16_t previous, uint8_t byte);
/* data may be NULL only when length is zero. */
uint16_t charge_crc16(const uint8_t *data, uint32_t length);
#endif
