#include "charge/protocol.h"

/* Behavioral source: recovery/reconstructed/serial_protocol.c, 0x08008EAC.
 * Hardware calls are represented by values; storage belongs to the caller.
 */
ChargeSerialEvent charge_serial_feed(ChargeSerialParser *state,
    uint8_t buffer[CHARGE_SERIAL_RX_CAPACITY], uint8_t byte)
{
    if (state->index == 0) {
        switch (byte) {
        case 0x55: state->mode = 0; state->expected = 9; break;
        case 0x44: state->mode = 2; state->expected = 27; break;
        case 0xaa: state->mode = 1; state->expected = 9; break;
        default: return CHARGE_SERIAL_NONE;
        }
        buffer[0] = byte;
        state->index = 1;
        return CHARGE_SERIAL_NONE;
    }
    if (state->index == 1) {
        if (byte == 0xaa) {
            buffer[1] = byte;
            state->index = 2;
        } else if (buffer[0] == 0x55 || buffer[0] == 0xaa) {
            if (buffer[0] == 0x55) state->mode = 1;
            buffer[1] = byte;
            state->index = 2;
            state->expected = (uint8_t)(byte + 2);
        } else {
            state->index = 0;
        }
        return CHARGE_SERIAL_NONE;
    }
    if ((int)state->index != (int)state->expected - 1) {
        buffer[state->index] = byte;
        ++state->index;
        return CHARGE_SERIAL_NONE;
    }
    ChargeSerialEvent event = CHARGE_SERIAL_NONE;
    if (state->mode == 0) {
        uint8_t checksum = 0;
        for (unsigned i = 0; i < 8; ++i) checksum ^= buffer[i];
        if (checksum == byte) event = CHARGE_SERIAL_FIXED55;
    } else if (state->mode == 2) {
        uint8_t checksum = byte;
        for (unsigned i = 0; i + 1 < state->expected; ++i)
            checksum ^= buffer[i];
        if (checksum == 0) event = CHARGE_SERIAL_FIXED44;
    }
    state->index = 0;
    return event;
}

/* Behavioral source: original complete-block checker at 0x08008E84. */
bool charge_serial_block_valid(const uint8_t *frame, uint16_t length)
{
    if (frame == NULL || length < 2) return false;
    uint8_t checksum = 0;
    for (uint16_t i = 1; i < length - 1; ++i) checksum ^= frame[i];
    return checksum == frame[length - 1];
}

/* Behavioral source: original response builder at 0x0800C7C4. */
uint16_t charge_serial_build_frame(uint8_t *out, size_t capacity,
    uint8_t command, uint8_t payload_length, uint8_t subcommand,
    const uint8_t *payload, uint8_t prefix)
{
    if (payload_length > CHARGE_SERIAL_MAX_PAYLOAD || out == NULL ||
        capacity < (size_t)payload_length + 5 ||
        (payload_length != 0 && payload == NULL)) return 0;
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

/* Behavioral source: identifier response at 0x0800964E. */
uint16_t charge_serial_build_identifier_response(uint8_t *out, size_t capacity,
    const uint8_t *id, const uint8_t *mode_record)
{
    uint8_t payload[6];
    if (id == NULL || mode_record == NULL) return 0;
    if (mode_record[0] == 0x55) payload[5] = 0;
    else if (mode_record[0] == 0x66) payload[5] = 1;
    else return 0;
    for (unsigned i = 0; i < 4; ++i) payload[i] = id[i];
    payload[4] = mode_record[2];
    return charge_serial_build_frame(out, capacity, 0x10, 6, 1, payload, 0xaa);
}
