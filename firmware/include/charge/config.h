#ifndef CHARGE_CONFIG_H
#define CHARGE_CONFIG_H

#include <stdint.h>

enum { CHARGE_CONFIG_SIZE = 120, CHARGE_PARAMETER_PAYLOAD_SIZE = 23 };

/* Apply the recovered wire layout to caller-owned storage. Field offsets are
 * intentional: physical units and names are not fully established. Only value
 * 1 selects big endian; all other values select little endian, as before.
 * Untouched bytes are retained; byte 118 is the dirty flag. NULL payload is a
 * no-op. Otherwise config and payload must cover the declared sizes and must
 * not overlap. Serial framing and persistence belong to callers.
 */
void charge_config_apply_payload(uint8_t config[CHARGE_CONFIG_SIZE],
    const uint8_t payload[CHARGE_PARAMETER_PAYLOAD_SIZE], uint8_t big_endian);

#endif
