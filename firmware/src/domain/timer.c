#include "charge/timer.h"
uint16_t charge_timer_delta(uint16_t now, uint16_t previous)
{
    return now < previous ? 1u : (uint16_t)(now - previous);
}
uint8_t charge_timer_subtract(uint16_t *remaining, uint16_t delta)
{
    if (*remaining == 0) return 0;
    if (*remaining > delta) {
        *remaining = (uint16_t)(*remaining - delta);
        return 0;
    }
    *remaining = 0;
    return 1;
}
