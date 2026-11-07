#ifndef CHARGE_TIMER_H
#define CHARGE_TIMER_H
#include <stdint.h>
enum { CHARGE_TIMER_COUNT = 93 };
/* Compatibility rule: any backwards/wrapped sample advances exactly one tick.
 * The tick duration is supplied by the platform, not assumed to be milliseconds. */
uint16_t charge_timer_delta(uint16_t now, uint16_t previous);
/* Returns one only when an active timer expires in this subtraction. The caller
 * still owns expiration dispatch and periodic actions (not implemented here). */
uint8_t charge_timer_subtract(uint16_t *remaining, uint16_t delta);
#endif
