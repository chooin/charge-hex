#include "charge/channel.h"
#include "charge/timer.h"
#include "charge/storage.h"
#include "charge/crc16.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned writes, reads, probes, tick_calls;
    unsigned fail_write, busy_probes;
    uint32_t start, step;
    uint16_t address[8], size[8];
    const uint8_t *data[8];
} FakeStorage;
static uint32_t read_port(void *context, uint16_t address, uint8_t *data,
                           uint16_t size, uint32_t timeout)
{
    FakeStorage *f = context;
    ++f->reads;
    assert(address == 65535 && size == 1 && timeout == 1000);
    data[0] = 0x42;
    return 7; /* Read statuses propagate instead of being collapsed to 1. */
}
static uint32_t write_port(void *context, uint16_t address, const uint8_t *data,
                            uint16_t size, uint32_t timeout)
{
    FakeStorage *f = context;
    assert(timeout == 500 && f->writes < 8);
    f->address[f->writes] = address;
    f->size[f->writes] = size;
    f->data[f->writes] = data;
    return ++f->writes == f->fail_write ? 7 : 0;
}
static uint32_t probe_port(void *context, uint32_t timeout)
{
    FakeStorage *f = context;
    assert(timeout == 50);
    return ++f->probes <= f->busy_probes ? 7 : 0;
}
static uint32_t tick_port(void *context)
{
    FakeStorage *f = context;
    return f->start + f->step * f->tick_calls++;
}
static void test_storage(void)
{
    FakeStorage f = {0};
    ChargeStorage s = {&f, read_port, write_port, probe_port, tick_port};
    uint8_t data[300] = {0};
    assert(charge_storage_write(&s, 127, data, 258) == 0);
    assert(f.writes == 4 && f.probes == 4 && f.tick_calls == 4);
    const uint16_t addresses[] = {127,128,256,384}, sizes[] = {1,128,128,1};
    const unsigned offsets[] = {0,1,129,257};
    for (unsigned i = 0; i < 4; ++i) {
        assert(f.address[i] == addresses[i] && f.size[i] == sizes[i]);
        assert(f.data[i] == data + offsets[i]);
    }
    memset(&f, 0, sizeof f);
    f.fail_write = 2;
    assert(charge_storage_write(&s, 127, data, 258) == 1);
    assert(f.writes == 2 && f.probes == 1);
    memset(&f, 0, sizeof f);
    assert(charge_storage_write(&s, 65535, data, 2) == 1);
    assert(f.writes == 0 && f.probes == 0);
    assert(charge_storage_read(&s, 65535, data, 2) == 1 && f.reads == 0);
    assert(charge_storage_read(&s, 65535, data, 1) == 7 && data[0] == 0x42);
    assert(charge_storage_write(&s, 65535, data, 1) == 0);
    memset(&f, 0, sizeof f);
    assert(charge_storage_write(&s, 0, NULL, 0) == 0);
    assert(f.writes == 1 && f.size[0] == 0 && f.probes == 1);
    memset(&f, 0, sizeof f);
    f.start = UINT32_MAX - 100;
    f.step = 250;
    f.busy_probes = 2;
    assert(charge_storage_wait_ready(&s) == 0);
    assert(f.probes == 3 && f.tick_calls == 3); /* 500 is not timed out. */
    memset(&f, 0, sizeof f);
    f.start = UINT32_MAX - 100;
    f.step = 250;
    f.busy_probes = 10;
    assert(charge_storage_wait_ready(&s) == 1);
    assert(f.probes == 3 && f.tick_calls == 4); /* 750 expires after wrap. */
    memset(&f, 0, sizeof f);
    assert(charge_storage_write(&s, 0, NULL, 1) == 1 && f.writes == 0);
    ChargeStorage missing = {0};
    assert(charge_storage_read(&missing, 0, data, 1) == 1);
    assert(charge_storage_write(&missing, 0, data, 1) == 1);
    assert(charge_storage_wait_ready(&missing) == 1);
    assert(charge_storage_wait_ready(NULL) == 1);
}
static void test_channel_timer(void)
{
    uint32_t bits = 0xa5a5ffffu;
    uint8_t packed[3] = {0xff,0xff,0xff};
    charge_channel_set_state(&bits, packed, 11, 0);
    assert(bits == 0xa5a5f7ffu && packed[2] == 0x7f);
    charge_channel_set_state(&bits, packed, 11, 255);
    assert(bits == 0xa5a5ffffu && packed[2] == 0xbf);
    charge_channel_set_state(&bits, packed, 12, 0);
    assert(bits == 0xa5a5ffffu && packed[2] == 0xbf);
    ChargeChannel channel;
    memset(&channel, 0xa5, sizeof channel);
    charge_channel_clear_accounting(&channel);
    assert(channel.field_18 == 0 && channel.field_1a == 0 && channel.field_24 == 0);
    assert(channel.field_28 == 0 && channel.field_1c == 0 && channel.field_0c == 0);
    assert(channel.countdown == 0xa5a5a5a5u && channel.state_16 == 0xa5);
    assert(charge_timer_delta(0, 65535) == 1);
    assert(charge_timer_delta(2, 65530) == 1); /* Not modulo arithmetic. */
    assert(charge_timer_delta(4, 4) == 0 && charge_timer_delta(9, 4) == 5);
    uint16_t t = 10;
    assert(charge_timer_subtract(&t, 0) == 0 && t == 10);
    assert(charge_timer_subtract(&t, 9) == 0 && t == 1);
    assert(charge_timer_subtract(&t, 1) == 1 && t == 0);
    assert(charge_timer_subtract(&t, 65535) == 0 && t == 0);
    t = 1;
    assert(charge_timer_subtract(&t, 65535) == 1 && t == 0);
}
int main(void)
{
    test_channel_timer();
    test_storage();
    assert(charge_crc16(NULL, 0) == 0);
    assert(charge_crc16((const uint8_t *)"123456789", 9) == 0x31c3);
    puts("domain/services: PASS (channel, timer, CRC, storage boundaries and failures)");
    return 0;
}
