#include "charge/config.h"
#include "charge/protocol.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    uint8_t out[CHARGE_SERIAL_TX_CAPACITY];
    uint8_t payload[CHARGE_SERIAL_MAX_PAYLOAD] = {0};
    memset(out, 0x5a, sizeof out);
    assert(charge_serial_build_frame(out, 4, 1, 0, 2, NULL, 0xaa) == 0);
    assert(out[0] == 0x5a);
    assert(charge_serial_build_frame(out, sizeof out, 1, 1, 2, NULL, 0xaa) == 0);
    assert(out[0] == 0x5a);
    assert(charge_serial_build_frame(out, sizeof out, 1, 0, 2, NULL, 0xaa) == 5);
    assert(memcmp(out, (uint8_t[]){0xaa, 3, 1, 2, 0}, 5) == 0);
    assert(charge_serial_build_frame(out, sizeof out, 0x10, 166, 1, payload, 0x55) == 171);
    assert(charge_serial_block_valid(out, 171));
    out[0] ^= 0xff;
    assert(charge_serial_block_valid(out, 171));
    out[4] ^= 1;
    assert(!charge_serial_block_valid(out, 171));
    assert(!charge_serial_block_valid(NULL, 2));
    assert(!charge_serial_block_valid(out, 0));
    assert(!charge_serial_block_valid(out, 1));

    uint8_t id[] = {1, 2, 3, 4};
    uint8_t mode[] = {0x55, 0, 8};
    assert(charge_serial_build_identifier_response(out, sizeof out, id, mode) == 11);
    assert(out[9] == 0 && out[8] == 8 && memcmp(out + 4, id, 4) == 0);
    mode[0] = 0x66;
    assert(charge_serial_build_identifier_response(out, sizeof out, id, mode) == 11);
    assert(out[9] == 1);
    mode[0] = 0;
    memset(out, 0x5a, sizeof out);
    assert(charge_serial_build_identifier_response(out, sizeof out, id, mode) == 0);
    assert(out[0] == 0x5a);

    ChargeSerialParser state = {0};
    uint8_t buffer[CHARGE_SERIAL_RX_CAPACITY] = {0};
    uint8_t fixed[] = {0x55, 0xaa, 1, 2, 3, 4, 5, 6, 0xf8};
    for (unsigned i = 0; i < 8; ++i)
        assert(charge_serial_feed(&state, buffer, fixed[i]) == CHARGE_SERIAL_NONE);
    assert(charge_serial_feed(&state, buffer, fixed[8]) == CHARGE_SERIAL_FIXED55);
    assert(state.index == 0 && buffer[8] == 0);
    assert(charge_serial_feed(&state, buffer, 0xaa) == CHARGE_SERIAL_NONE);
    assert(charge_serial_feed(&state, buffer, 0xfe) == CHARGE_SERIAL_NONE);
    assert(state.expected == 0);
    for (unsigned i = 2; i < 256; ++i)
        assert(charge_serial_feed(&state, buffer, 7) == CHARGE_SERIAL_NONE);
    assert(state.index == 0 && buffer[255] == 7);

    uint8_t config[CHARGE_CONFIG_SIZE];
    uint8_t parameters[CHARGE_PARAMETER_PAYLOAD_SIZE];
    memset(config, 0xa5, sizeof config);
    memset(parameters, 0xff, sizeof parameters);
    config[42] = 1; config[43] = 0;
    charge_config_apply_payload(config, parameters, 0);
    assert(config[0] == 0xa5 && config[119] == 0xa5 && config[118] == 1);
    assert(config[2] == 240 && config[3] == 0);
    assert(config[6] == 10 && config[7] == 0);
    assert(config[12] == 0xc4 && config[13] == 9);
    assert(config[32] == 0xc4 && config[33] == 0x3b);
    config[118] = 0;
    charge_config_apply_payload(config, NULL, 0);
    assert(config[118] == 0);
    puts("protocol host contracts: PASS");
    return 0;
}
