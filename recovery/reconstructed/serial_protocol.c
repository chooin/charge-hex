/* Analyst-written semantic reconstruction, not original source.
 * Evidence: firmware Thumb addresses listed below. No hardware was executed.
 * This module compiles for review but external fw_* routines remain unresolved;
 * it is not a replacement firmware. Explicit state/output parameters below are
 * analysis conveniences replacing the original fixed-address globals.
 */
#include <stdint.h>
#include <stddef.h>
#define SERIAL_M8(a) (*(volatile uint8_t *)(uintptr_t)(a))

/* Fixed frame state was at 0x20000124; buffer at 0x20001024. */
typedef struct { uint8_t mode, expected, index; } SerialParser;
extern void serial_on_fixed55(void); /* original 0x08009694, consumes global buffer */
extern void serial_on_fixed44(const uint8_t *payload); /* original 0x0800C830 */
extern void serial_on_block(const uint8_t *frame); /* original 0x0800B0DC */

/* 0x08008EAC. No bounds validation in the original. Caller must provide storage
 * for the 8-bit index (256 bytes for arbitrary malformed input in a host model).
 * In the firmware the next object is only 32 bytes after buffer start; do not
 * mistake the host model storage requirement for the original buffer allocation.
 */
void serial_feed_byte(SerialParser *s, uint8_t *buffer, uint8_t byte)
{
    if (s->index == 0) {
        switch (byte) {
        case 0x55: s->mode = 0; s->expected = 9; break;
        case 0x44: s->mode = 2; s->expected = 27; break;
        case 0xaa: s->mode = 1; s->expected = 9; break;
        default: s->index = 0; return;
        }
        buffer[0] = byte;
        s->index = 1;
        return;
    }
    if (s->index == 1) {
        if (byte == 0xaa) {
            buffer[1] = byte;
            s->index = 2;
        } else if (buffer[0] == 0x55 || buffer[0] == 0xaa) {
            if (buffer[0] == 0x55) s->mode = 1;
            buffer[1] = byte;
            s->index = 2;
            s->expected = (uint8_t)(byte + 2);
        } else {
            s->index = 0;
        }
        return;
    }
    if ((int)s->index != (int)s->expected - 1) {
        buffer[s->index] = byte;
        ++s->index; /* intentional uint8_t wrap, as in original STRB */
        return;
    }
    if (s->mode == 0) {
        uint8_t x = 0;
        for (unsigned i = 0; i < 8; ++i) x ^= buffer[i];
        if (x == byte) serial_on_fixed55();
    } else if (s->mode == 2) {
        uint8_t x = byte;
        for (unsigned i = 0; i < (unsigned)s->expected - 1; ++i) x ^= buffer[i];
        if (x == 0) serial_on_fixed44(buffer + 3);
    }
    /* Mode 1 has NO dispatch in this routine. Final checksum is not stored. */
    s->index = 0;
}

/* 0x08008E84: separate complete-block RX path. Valid-input precondition length>=2.
 * Byte 0 is excluded from this checksum; this differs from fixed frames above.
 */
void serial_dispatch_block(const uint8_t *frame, uint16_t length)
{
    uint8_t checksum = 0;
    for (uint16_t i = 1; i < (int)length - 1; ++i) checksum ^= frame[i];
    if (frame[length - 1] == checksum) serial_on_block(frame);
}

/* 0x0800C7C4. Original output buffer 0x20000A18, then calls 0x0800947C.
 * Returns 0 for original no-send case; returned length is an analyst convenience.
 * Capacity requirement for out is at least payload_length+5 bytes.
 */
uint16_t serial_build_frame(uint8_t *out, uint8_t command, uint8_t payload_length,
                           uint8_t subcommand, const uint8_t *payload, uint8_t prefix)
{
    if (payload_length > 166) return 0;
    out[0] = prefix;
    out[1] = (uint8_t)(payload_length + 3);
    out[2] = command;
    out[3] = subcommand;
    for (unsigned i = 0; i < payload_length; ++i) out[i + 4] = payload[i];
    out[payload_length + 4] = 0;
    for (unsigned i = 1; i < (unsigned)payload_length + 4; ++i)
        out[payload_length + 4] ^= out[i];
    return (uint16_t)(payload_length + 5);
}

extern int fw_08007280_uart_transmit_dma(void *handle, const uint8_t *data, uint16_t n);
/* 0x0800947C / 0x080094B4. Names USART1/2 follow IRQ/handle cross-reference.
 * On successful DMA launch, waits on a completion byte with no local timeout.
 */
void serial_usart1_send(const uint8_t *data, uint16_t n)
{
    SERIAL_M8(0x20000E13) = 1;
    if (fw_08007280_uart_transmit_dma((void *)(uintptr_t)0x20001044, data, n) == 0)
        while (SERIAL_M8(0x20000E13) == 1) { }
}
void serial_usart2_send(const uint8_t *data, uint16_t n)
{
    SERIAL_M8(0x20001017) = 1;
    if (fw_08007280_uart_transmit_dma((void *)(uintptr_t)0x200010C8, data, n) == 0)
        while (SERIAL_M8(0x20001017) == 1) { }
}

/* 0x0800964E: formats a response, then original 0xC7C4 sends it on USART1.
 * id[0..3] copied as bytes; mode_record[0]==55 or 66 determines final payload byte.
 * Caller supplies out>=11 bytes. Zero means original no-send case.
 */
uint16_t serial_build_identifier_response(uint8_t *out, const uint8_t *id,
                                         const uint8_t *mode_record)
{
    uint8_t payload[6];
    if (!id || !mode_record) return 0;
    for (unsigned i = 0; i < 4; ++i) payload[i] = id[i];
    if (mode_record[0] == 0x55) payload[5] = 0;
    else if (mode_record[0] == 0x66) payload[5] = 1;
    else return 0;
    payload[4] = mode_record[2];
    return serial_build_frame(out, 0x10, 6, 1, payload, 0xaa);
}

static uint16_t serial_u16(const uint8_t *p, uint8_t big_endian)
{
    return big_endian == 1 ? (uint16_t)((uint16_t)p[0] << 8 | p[1])
                          : (uint16_t)((uint16_t)p[1] << 8 | p[0]);
}
static uint16_t serial_get_config(const uint8_t *c, unsigned offset)
{
    return (uint16_t)((uint16_t)c[offset + 1] << 8 | c[offset]);
}
static void serial_set_config(uint8_t *c, unsigned offset, uint16_t value)
{
    c[offset] = (uint8_t)value;
    c[offset + 1] = (uint8_t)(value >> 8);
}

/* 0x0800BCD8 with 0x0800A6A0 helper. Original config base 0x20000854.
 * p must contain 23 bytes; config must contain at least 119 bytes.
 * Field meanings/units remain unknown; offsets preserve evidence.
 * 0xC830 passes big_endian=0 (little-endian 16-bit fields).
 */
void serial_apply_parameter_payload(uint8_t *config, const uint8_t *p, uint8_t big_endian)
{
    if (!p) return;
    serial_set_config(config,  2, serial_u16(p, big_endian));
    serial_set_config(config,  4, serial_u16(p + 2, big_endian));
    serial_set_config(config,  8, p[4]);
    serial_set_config(config, 10, p[5]);
    serial_set_config(config,  6, p[6]);
    serial_set_config(config, 12, serial_u16(p + 7, big_endian));
    serial_set_config(config, 14, serial_u16(p + 9, big_endian));
    serial_set_config(config, 16, serial_u16(p + 11, big_endian));
    serial_set_config(config, 18, serial_u16(p + 13, big_endian));
    for (unsigned i = 0; i < 6; ++i) serial_set_config(config, 20 + 2*i, p[15+i]);
    serial_set_config(config, 32, (uint16_t)(p[21] * 60u));
    serial_set_config(config, 34, p[22]);
    uint32_t limit = (uint32_t)serial_get_config(config, 42) * 60u / 60u;
    if (serial_get_config(config, 2) > limit) serial_set_config(config, 2, 240);
    if (serial_get_config(config, 4) > limit) serial_set_config(config, 4, 240);
    if (serial_get_config(config, 6) > 250) serial_set_config(config, 6, 10);
    for (unsigned off = 12; off <= 18; off += 2)
        if (serial_get_config(config, off) > 2500) serial_set_config(config, off, 2500);
    config[118] = 1;
}

/* 0x0800C830 wrapper. counter is uint16_t at 0x2000012A.
 * The event function 0xCDB8 receives 0x26. The numeric unit of the counter is
 * not inferred here. Later reads/writes of the counter can occur in interrupts.
 */
extern void fw_0800cdb8_event(uint8_t event);
void serial_accept_parameter_frame(uint8_t *config, volatile uint16_t *counter,
                                   const uint8_t *payload)
{
    if (*counter != 0) { *counter = 1600; return; }
    *counter = 800;
    serial_apply_parameter_payload(config, payload, 0);
    fw_0800cdb8_event(0x26);
    *counter = 1600;
}
