/* Explicit register-state ABI for the recovered application main.
 * This is an offline semantic reference, not an MCU executable replacement.
 * External calls must implement the complete CPU/memory effects that matter to
 * main, including r0-r3/r12/lr/APSR; no dummy success implementations exist.
 */
#ifndef RECOVERY_APPLICATION_MAIN_H
#define RECOVERY_APPLICATION_MAIN_H
#include <stdint.h>
#include <stddef.h>
struct AppMainState;
typedef int (*AppMainCall)(void *, uint32_t target, struct AppMainState *);
typedef uint32_t (*AppMainIoRead)(void *, uint32_t address, unsigned width);
typedef void (*AppMainIoWrite)(void *, uint32_t address, unsigned width, uint32_t value);
typedef struct AppMainState {
    uint32_t r[16];
    uint32_t apsr; /* NZCV in bits 31..28, other bits retained */
    uint32_t pc;
    uint32_t fault_address;
    int32_t fault;
    uint64_t main_instruction_count;
    uint8_t *flash; /* exactly 65536 bytes at 0x08000000 */
    uint8_t *sram;
    uint32_t sram_size;
    void *user;
    AppMainCall call;
    AppMainIoRead io_read;
    AppMainIoWrite io_write;
} AppMainState;
/* Set pc=0x0800A708 for initialization, or resume a previously yielded state.
 * 0 = instruction budget consumed, 1 = external call requested a yield,
 * -1 = unmapped memory/entry, -2 = required external-call callback absent.
 * The enclosing hardware, IRQ schedule, and callee implementations are caller
 * responsibilities. A callback returning nonzero yields AFTER the BL.
 */
int recovered_application_main_run(AppMainState *state, uint32_t budget);
#endif
