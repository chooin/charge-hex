#include "charge/channel.h"

void charge_channel_set_state(volatile uint32_t *bits, volatile uint8_t packed[3],
                              uint8_t channel, uint8_t enabled)
{
    if (channel >= CHARGE_CHANNEL_COUNT) return;
    uint32_t mask = (uint32_t)1u << channel;
    uint32_t previous = *bits;
    *bits = enabled ? previous | mask : previous & ~mask;
    uint8_t shift = (uint8_t)((channel & 3u) * 2u);
    uint8_t value = packed[channel / 4u];
    packed[channel / 4u] = (uint8_t)((value & ~(3u << shift)) |
                                   ((enabled ? 2u : 1u) << shift));
}

void charge_channel_clear_accounting(volatile ChargeChannel *channel)
{
    channel->field_18 = 0;
    channel->field_1a = 0;
    channel->field_24 = 0;
    channel->field_28 = 0;
    channel->field_1c = 0;
    channel->field_0c = 0;
}
