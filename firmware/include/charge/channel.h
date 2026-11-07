#ifndef CHARGE_CHANNEL_H
#define CHARGE_CHANNEL_H
#include <stddef.h>
#include <stdint.h>

enum { CHARGE_CHANNEL_COUNT = 12, CHARGE_CHANNEL_RECORD_SIZE = 52 };

/* Wire/storage layout observed in the original application. Unknown units keep
 * offset names; this is not a claim that those fields have been identified. */
typedef struct {
    uint32_t countdown;
    uint16_t metric_04, metric_06;
    uint32_t accumulator_08;
    uint16_t field_0c, field_0e;
    uint32_t field_10;
    uint8_t level_14, band_15, state_16, flag_17;
    uint16_t field_18, field_1a, field_1c, field_1e;
    uint32_t field_20, field_24;
    uint16_t field_28, field_2a;
    uint8_t mode_2c, display_2d, flag_2e, flag_2f;
    uint8_t flag_30, flag_31, flag_32, flag_33;
} ChargeChannel;
_Static_assert(sizeof(ChargeChannel) == CHARGE_CHANNEL_RECORD_SIZE, "channel stride");
_Static_assert(offsetof(ChargeChannel, state_16) == 0x16, "channel state offset");
_Static_assert(offsetof(ChargeChannel, field_24) == 0x24, "channel accounting offset");

/* The caller owns serialization against interrupts: volatile preserves accesses,
 * not atomicity of the two related state updates. Invalid channel is a no-op. */
void charge_channel_set_state(volatile uint32_t *bits, volatile uint8_t packed[3],
                              uint8_t channel, uint8_t enabled);
/* Requires a valid channel record; clears only the six observed fields. */
void charge_channel_clear_accounting(volatile ChargeChannel *channel);
#endif
