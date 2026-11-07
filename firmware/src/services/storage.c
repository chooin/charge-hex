#include "charge/storage.h"
#include <stddef.h>

uint32_t charge_storage_read(const ChargeStorage *s, uint16_t address,
                             uint8_t *data, uint16_t size)
{
    if (s == NULL || s->read == NULL || (data == NULL && size != 0) ||
        0x10000u - address < size) return 1;
    return s->read(s->context, address, data, size, 1000);
}

uint32_t charge_storage_wait_ready(const ChargeStorage *s)
{
    if (s == NULL || s->probe == NULL || s->tick == NULL) return 1;
    uint32_t start = s->tick(s->context);
    while (s->probe(s->context, 50) != 0) {
        if ((uint32_t)(s->tick(s->context) - start) > 500) return 1;
    }
    return 0;
}

static uint32_t write_chunk(const ChargeStorage *s, uint16_t address,
                            const uint8_t *data, uint16_t size)
{
    if (s->write(s->context, address, data, size, 500) != 0) return 1;
    return charge_storage_wait_ready(s);
}

uint32_t charge_storage_write(const ChargeStorage *s, uint16_t address,
                              const uint8_t *data, uint16_t size)
{
    if (s == NULL || s->write == NULL || s->probe == NULL || s->tick == NULL ||
        (data == NULL && size != 0) || 0x10000u - address < size) return 1;
    uint16_t first = (uint16_t)(CHARGE_STORAGE_PAGE_SIZE - (address & 127u));
    if (first >= size) return write_chunk(s, address, data, size);
    uint16_t remaining = (uint16_t)(size - first);
    if (write_chunk(s, address, data, first) != 0) return 1;
    address = (uint16_t)(address + first);
    data += first;
    while (remaining >= CHARGE_STORAGE_PAGE_SIZE) {
        if (write_chunk(s, address, data, CHARGE_STORAGE_PAGE_SIZE) != 0) return 1;
        address = (uint16_t)(address + CHARGE_STORAGE_PAGE_SIZE);
        data += CHARGE_STORAGE_PAGE_SIZE;
        remaining = (uint16_t)(remaining - CHARGE_STORAGE_PAGE_SIZE);
    }
    return remaining == 0 ? 0 : write_chunk(s, address, data, remaining);
}
