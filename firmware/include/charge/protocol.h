#ifndef CHARGE_PROTOCOL_H
#define CHARGE_PROTOCOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum {
    CHARGE_SERIAL_RX_CAPACITY = 256,
    CHARGE_SERIAL_MAX_PAYLOAD = 166,
    CHARGE_SERIAL_TX_CAPACITY = 171,
    CHARGE_SERIAL_IDENTIFIER_FRAME_SIZE = 11
};

typedef struct {
    uint8_t mode;
    uint8_t expected;
    uint8_t index;
} ChargeSerialParser;

typedef enum {
    CHARGE_SERIAL_NONE = 0,
    CHARGE_SERIAL_FIXED55 = 1,
    CHARGE_SERIAL_FIXED44 = 2
} ChargeSerialEvent;

/* Initialize state and storage to zero before the first byte. A parser owns one
 * independent buffer. The returned event borrows that buffer until the next
 * feed. FIXED55 consumes buffer[0..7]; FIXED44 payload starts at buffer + 3.
 * The final checksum byte is not stored. Dispatch the event synchronously.
 *
 * This compatibility parser deliberately preserves the 8-bit index wrapping
 * and the original absence of mode-1 dispatch. All 256 bytes are required for
 * arbitrary malformed streams; this is not the original MCU allocation size.
 * The state must only be initialized or modified by this function.
 */
ChargeSerialEvent charge_serial_feed(ChargeSerialParser *state,
    uint8_t buffer[CHARGE_SERIAL_RX_CAPACITY], uint8_t byte);

/* Complete-block RX is a separate path: XOR excludes byte zero. Buffers shorter
 * than two bytes are rejected. No transport or command dispatch occurs here.
 */
bool charge_serial_block_valid(const uint8_t *frame, uint16_t length);

/* Needs payload_length + 5 output bytes (maximum 171). Zero means no output:
 * invalid pointer/capacity or payload_length > 166. Output stays untouched on
 * rejection. A NULL payload is permitted only for zero payload_length.
 * Input and output buffers must not overlap.
 */
uint16_t charge_serial_build_frame(uint8_t *out, size_t capacity,
    uint8_t command, uint8_t payload_length, uint8_t subcommand,
    const uint8_t *payload, uint8_t prefix);

/* id has four bytes; mode_record has at least three bytes. Only modes 0x55 and
 * 0x66 produce an 11-byte frame; other modes leave output untouched.
 */
uint16_t charge_serial_build_identifier_response(uint8_t *out, size_t capacity,
    const uint8_t *id, const uint8_t *mode_record);

#endif
