/* Explicit whole-firmware CPU/bus state. NOT MCU-production firmware source.
 * All recognized Thumb instructions are compiled C, including callee bodies.
 * Bus callbacks must provide peripheral/alias/Flash-controller semantics;
 * missing bus callbacks fail explicitly instead of returning dummy success.
 */
#ifndef RECOVERED_FULL_C_MODEL_H
#define RECOVERED_FULL_C_MODEL_H
#include <stdint.h>
#include <stddef.h>
struct FwMachine;
typedef uint32_t (*FwBusRead)(void *, struct FwMachine *, uint32_t address, unsigned width);
typedef void (*FwBusWrite)(void *, struct FwMachine *, uint32_t address, unsigned width, uint32_t value);
typedef void (*FwEvent)(void *, struct FwMachine *, unsigned kind, uint32_t value);
typedef struct FwMachine {
 uint32_t r[16];
 uint32_t apsr; /* NZCV bits 31..28 */
 uint32_t pc;
 uint32_t primask;
 uint32_t stop_address;
 uint32_t fault_address;
 int32_t fault;
 uint64_t instructions;
 const uint8_t *flash;
 uint8_t *sram;
 uint32_t sram_size;
 void *user;
 FwBusRead bus_read;
 FwBusWrite bus_write;
 FwEvent event;
} FwMachine;
extern const uint8_t recovered_flash_image[65536];
/* Events: 1 DSB, 2 ISB, 3 CPS(PRIMASK), 4 MSR(MSP).
 * Run returns: 0 budget consumed, 1 stop_address reached;
 * -1 unclassified PC, -2 missing/faulting bus, -3 non-Thumb BX/POP target,
 * -4 exception return not modeled, -5 unaligned halfword/word access.
 * First memory fault is retained and later memory operations are suppressed.
 * Precise exception entry/register rollback is not modeled.
 */
void recovered_firmware_init(FwMachine *, uint8_t *sram, uint32_t sram_size);
int recovered_firmware_run(FwMachine *, uint32_t instruction_budget);
#endif
