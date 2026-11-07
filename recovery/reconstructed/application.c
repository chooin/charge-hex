/*
 * Analyst reconstruction from stm32_fw.hex, not original source.
 * Thumb instruction addresses are the evidence anchors. This file is a partial
 * semantic recovery for review; external fw_* functions are unresolved original
 * routines, so this is NOT a linkable or flashable replacement firmware.
 * Board photo identifies Geehy APM32F030C8T6; register names use the
 * compatible ST STM32F0 map. Hardware roles and units not
 * established by instructions deliberately retain neutral names.
 */
#include <stdint.h>
#include <stddef.h>
#define M8(a)  (*(volatile uint8_t *)(uintptr_t)(a))
#define M16(a) (*(volatile uint16_t *)(uintptr_t)(a))
#define M32(a) (*(volatile uint32_t *)(uintptr_t)(a))

/* 12 objects, 52 bytes each, observed in 0x08009D84 and 0x0800ACB8. */
typedef struct {
    uint32_t countdown;        /* +0: decremented with elapsed ticks; inferred name */
    uint16_t metric_04;        /* +4: physical unit not established */
    uint16_t metric_06;        /* +6 */
    uint32_t accumulator_08;   /* +8 */
    uint16_t field_0c, field_0e;
    uint32_t field_10;
    uint8_t level_14, band_15, state_16, flag_17;
    uint16_t field_18, field_1a, field_1c, field_1e;
    uint32_t field_20, field_24;
    uint16_t field_28, field_2a;
    uint8_t mode_2c, display_2d, flag_2e, flag_2f;
    uint8_t flag_30, flag_31, flag_32, flag_33;
} RecoveredChannel;
_Static_assert(sizeof(RecoveredChannel) == 52, "observed channel stride");
_Static_assert(offsetof(RecoveredChannel, state_16) == 22, "state offset");
#define CHANNELS ((volatile RecoveredChannel *)(uintptr_t)0x200005E4)

extern void fw_0800b0dc_dispatch_frame(const uint8_t *frame);
extern void fw_08009694_handle_fixed_frame(void);
extern void fw_0800c830_handle_44_payload(const uint8_t *payload);
extern void fw_08005d46_gpio_write(uint32_t port, uint16_t pins, uint32_t state);
extern void fw_080086b8_delay(uint32_t count);
extern void fw_0800cc44_delay(uint32_t count);
extern void fw_0800cc64_delay(uint32_t count);

/* 0x08008E84..0x08008EA8: caller supplies frame and length.
 * Valid-input precondition: accessible buffer, length >= 2.
 * XOR excludes header byte 0 and the final checksum byte.
 */
void recovered_dispatch_xor_frame(const uint8_t *frame, uint16_t length)
{
    uint8_t checksum = 0;
    for (uint16_t i = 1; i < (int)length - 1; ++i)
        checksum ^= frame[i];
    if (frame[length - 1] == checksum)
        fw_0800b0dc_dispatch_frame(frame);
}

/* 0x08008EAC..0x08008F78: byte-at-a-time parser.
 * State corresponds to 0x20000124..126; buffer at 0x20001024.
 * The original uses 8-bit expected length and write index and does not supply
 * a buffer length here. Keep those semantics; do not treat as hardened API.
 */
typedef struct { uint8_t mode, expected, index; } RecoveredParser;
void recovered_feed_byte(RecoveredParser *s, uint8_t *buffer, uint8_t byte)
{
    if (s->index == 0) {
        switch (byte) {
        case 0x55: buffer[0] = byte; s->index = 1; s->mode = 0; s->expected = 9; return;
        case 0x44: buffer[0] = byte; s->index = 1; s->mode = 2; s->expected = 27; return;
        case 0xaa: buffer[0] = byte; s->index = 1; s->mode = 1; s->expected = 9; return;
        default: s->index = 0; return;
        }
    }
    if (s->index == 1) {
        if (byte == 0xaa) { buffer[1] = byte; s->index = 2; return; }
        if (buffer[0] == 0x55) s->mode = 1;
        else if (buffer[0] != 0xaa) { s->index = 0; return; }
        buffer[1] = byte;
        s->index = 2;
        s->expected = (uint8_t)(byte + 2);
        return;
    }
    if ((int)s->index != (int)s->expected - 1) {
        buffer[s->index] = byte;
        ++s->index;
        return;
    }
    if (s->mode == 0) {
        uint8_t checksum = 0;
        for (unsigned i = 0; i < 8; ++i) checksum ^= buffer[i];
        if (checksum == byte) fw_08009694_handle_fixed_frame();
    } else if (s->mode == 2) {
        uint8_t checksum = byte;
        for (uint8_t i = 0; i < (int)s->expected - 1; ++i) checksum ^= buffer[i];
        if (checksum == 0) fw_0800c830_handle_44_payload(buffer + 3);
    }
    /* Mode 1 has no dispatch at this completion branch in the observed image. */
    s->index = 0;
}

/* 0x0800C85C..0x0800CA2A: updates RAM, not a GPIO register directly.
 * bitset = 0x200000B8; packed_status[3] = 0x200000DD.
 * One bit per channel in bitset; two bits/channel in packed status.
 * The paired bits are 01 for off and 10 for on (naming inferred).
 */
void recovered_set_channel_state(uint8_t channel, uint8_t enabled)
{
    if (channel >= 12) return;
    uint32_t mask = (uint32_t)1 << channel;
    uint32_t bits = M32(0x200000B8);
    M32(0x200000B8) = enabled ? (bits | mask) : (bits & ~mask);
    uint8_t shift = (uint8_t)((channel & 3u) * 2u);
    uintptr_t address = 0x200000DDu + channel / 4u;
    uint8_t value = M8(address);
    value = (uint8_t)((value & ~(3u << shift)) | ((enabled ? 2u : 1u) << shift));
    M8(address) = value;
}

/* 0x08009E14..0x08009E2A. Callers establish channel bounds. */
void recovered_clear_channel_accounting(uint8_t channel)
{
    volatile RecoveredChannel *c = &CHANNELS[channel];
    c->field_18 = 0;
    c->field_1a = 0;
    c->field_24 = 0;
    c->field_28 = 0;
    c->field_1c = 0;
    c->field_0c = 0;
}

/* 0x0800A7DA..0x0800A7F6: faithful wrap behavior, not modulo delta. */
uint16_t recovered_scheduler_delta(uint16_t now, uint16_t previous)
{
    return now < previous ? 1u : (uint16_t)(now - previous);
}

/* 0x0800A7FE..0x0800A80C and 0x0800A884..A886.
 * Main has 93 uint16_t countdown slots at 0x200008D4.
 * This extracts only the subtraction; expiration dispatch and periodic special
 * actions remain in the original main. Return 1 means expiry this iteration.
 */
uint8_t recovered_timer_subtract(uint16_t *remaining, uint16_t delta)
{
    if (*remaining == 0) return 0;
    if (*remaining > delta) { *remaining -= delta; return 0; }
    *remaining = 0;
    return 1;
}

/* 0x0800882C..0x0800888A: LSB-first output, clock PB15, data PA8.
 * Only selector 1 emits bits. The final delay(5) occurs for all selectors.
 * Command family 0x40/0xC0/0x8A suggests a display driver; part unidentified.
 */
void recovered_display_write_byte(uint8_t value, uint8_t selector)
{
    if (selector == 1) {
        for (unsigned i = 0; i < 8; ++i) {
            fw_08005d46_gpio_write(0x48000400, 1u << 15, 0);
            fw_08005d46_gpio_write(0x48000000, 1u << 8, value & 1u);
            fw_080086b8_delay(10);
            fw_08005d46_gpio_write(0x48000400, 1u << 15, 1);
            fw_080086b8_delay(10);
            value >>= 1;
        }
        fw_08005d46_gpio_write(0x48000400, 1u << 15, 0);
    }
    fw_080086b8_delay(5);
}

/* 0x0800CDB8..0x0800CE56: one-wire pulse-width command on PB10.
 * The two delay routines have different semantics; preserve their arguments,
 * and do not label them milliseconds/microseconds without clock verification.
 * Possible audio/voice-module link is an inference, not established identity.
 */
void recovered_pulse_command(uint32_t command)
{
    if ((uint32_t)(command - 0xe0) >= 8u && command > 0x49) return;
    if (M8(0x200008CC) == 1 && (command < 0x36 || (uint32_t)(command - 0x40) <= 1u))
        M8(0x200008CC) = 0;
    fw_08005d46_gpio_write(0x48000400, 1u << 10, 0);
    fw_0800cc44_delay(5);
    for (unsigned i = 0; i < 8; ++i) {
        fw_08005d46_gpio_write(0x48000400, 1u << 10, 1);
        fw_0800cc64_delay((command & 1u) ? 720 : 240);
        fw_08005d46_gpio_write(0x48000400, 1u << 10, 0);
        fw_0800cc64_delay((command & 1u) ? 240 : 720);
        fw_08005d46_gpio_write(0x48000400, 1u << 10, 1);
        command >>= 1;
    }
    fw_0800cc44_delay(1);
}

/* 0x08007400..0x0800744A: 74HC595-compatible MSB-first shift output. */
extern void fw_080073e8_delay(uint8_t count);
void recovered_shift_output_byte(uint8_t value)
{
    for (unsigned i = 0; i < 8; ++i) {
        fw_08005d46_gpio_write(0x48000400, 1u << 8, 0);
        fw_08005d46_gpio_write(0x48000400, 1u << 3, (value >> (7u - i)) & 1u);
        fw_080073e8_delay(20);
        fw_08005d46_gpio_write(0x48000400, 1u << 8, 1);
        fw_080073e8_delay(20);
    }
}

/* 0x08007474..0x0800748C and 0x08007450..0x0800746E.
 * Two reads preserved: no claim of atomic snapshot under interrupts.
 */
void recovered_flush_channel_outputs(void)
{
    recovered_shift_output_byte((uint8_t)(M16(0x200000B8) >> 8));
    recovered_shift_output_byte(M8(0x200000B8));
    fw_08005d46_gpio_write(0x48000400, 1u << 5, 0);
    fw_080073e8_delay(20);
    fw_08005d46_gpio_write(0x48000400, 1u << 5, 1);
}

/* 0x0800CDA4..0x0800CDB0: preserve full 32-bit sum, no byte wrap. */
void recovered_send_configured_command(void)
{
    recovered_pulse_command((uint32_t)M8(0x200008CB) + 0xE0u);
}

/* 0x08007498 and 0x080074FC: external I2C memory storage.
 * Address range and 128-byte pages suggest 24C512-class EEPROM; actual part
 * identity is not proven. The HAL-style function names/signatures are inferred
 * from register/stack arguments. Valid public input domain: 16-bit address/size.
 */
extern uint32_t fw_08005fb8_i2c_mem_read(void *handle, uint16_t device,
    uint16_t address, uint16_t address_size, uint8_t *data, uint16_t size, uint32_t timeout);
extern uint32_t fw_0800610c_i2c_mem_write(void *handle, uint16_t device,
    uint16_t address, uint16_t address_size, const uint8_t *data, uint16_t size, uint32_t timeout);
extern uint32_t fw_08005ea8_i2c_ready(void *handle, uint16_t device,
    uint32_t trials, uint32_t timeout);
extern uint32_t fw_08005d54_get_tick(void);
#define STORAGE_I2C_HANDLE ((void *)(uintptr_t)0x20000B6C)

uint32_t recovered_storage_read(uint16_t address, uint8_t *data, uint16_t size)
{
    if (0x10000u - address < size) return 1;
    return fw_08005fb8_i2c_mem_read(STORAGE_I2C_HANDLE, 0xA0, address, 2,
                                  data, size, 1000);
}

/* 0x080074C4..0x080074F4: preserve trials=0, timeout=50 exactly. */
uint32_t recovered_storage_wait_ready(void)
{
    uint32_t start = fw_08005d54_get_tick();
    while (fw_08005ea8_i2c_ready(STORAGE_I2C_HANDLE, 0xA0, 0, 50) != 0) {
        if ((uint32_t)(fw_08005d54_get_tick() - start) > 500) return 1;
    }
    return 0;
}

static uint32_t recovered_storage_write_chunk(uint16_t address,
                                              const uint8_t *data, uint16_t size)
{
    if (fw_0800610c_i2c_mem_write(STORAGE_I2C_HANDLE, 0xA0, address, 2,
                                data, size, 500) != 0) return 1;
    return recovered_storage_wait_ready() != 0 ? 1u : 0u;
}

uint32_t recovered_storage_write(uint16_t address, const uint8_t *data, uint16_t size)
{
    if (0x10000u - address < size) return 1;
    uint16_t first = (uint16_t)(128u - (address & 127u));
    if (first >= size) return recovered_storage_write_chunk(address, data, size);
    uint16_t remaining = (uint16_t)(size - first);
    uint16_t pages = (uint16_t)(remaining / 128u);
    uint16_t tail = (uint16_t)(remaining % 128u);
    if (recovered_storage_write_chunk(address, data, first) != 0) return 1;
    address = (uint16_t)(address + first);
    data += first;
    while (pages-- != 0) {
        if (recovered_storage_write_chunk(address, data, 128) != 0) return 1;
        address = (uint16_t)(address + 128u);
        data += 128;
    }
    if (tail == 0) return 0;
    return recovered_storage_write_chunk(address, data, tail);
}
