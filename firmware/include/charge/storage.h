#ifndef CHARGE_STORAGE_H
#define CHARGE_STORAGE_H
#include <stdint.h>
enum { CHARGE_STORAGE_PAGE_SIZE = 128 };

/* Synchronous ports. Board address/handle/address-width belong to the adapter.
 * probe performs a zero-byte device transmission, not a trials-based HAL call.
 * tick must keep advancing while a probe reports busy; units match legacy ticks.
 * Buffers stay valid until return. Ports return zero on success. */
typedef struct {
    void *context;
    uint32_t (*read)(void *, uint16_t, uint8_t *, uint16_t, uint32_t);
    uint32_t (*write)(void *, uint16_t, const uint8_t *, uint16_t, uint32_t);
    uint32_t (*probe)(void *, uint32_t);
    uint32_t (*tick)(void *);
} ChargeStorage;

/* Out-of-range requests or missing required ports return 1 without I/O.
 * read preserves the port's status; write/probe failure is normalized to 1.
 * Zero length deliberately still calls the port, matching the original code.
 * NULL data is permitted only for a zero-length transfer. */
uint32_t charge_storage_read(const ChargeStorage *storage, uint16_t address,
                             uint8_t *data, uint16_t size);
uint32_t charge_storage_wait_ready(const ChargeStorage *storage);
uint32_t charge_storage_write(const ChargeStorage *storage, uint16_t address,
                              const uint8_t *data, uint16_t size);
#endif
