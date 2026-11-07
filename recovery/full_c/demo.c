/* Demonstrate explicit missing-peripheral failure without faking any device. */
#include "firmware_model.h"
#include <stdio.h>

int main(void)
{
    uint8_t sram[8192] = {0};
    FwMachine machine;
    recovered_firmware_init(&machine, sram, sizeof sram);
    int result = recovered_firmware_run(&machine, 100000);
    printf("result=%d pc=0x%08x fault_address=0x%08x instructions=%llu\n",
           result, machine.pc, machine.fault_address,
           (unsigned long long)machine.instructions);
    /* The demo deliberately installs no MMIO implementation. */
    if (result == -2) {
        puts("Stopped at an unmodeled peripheral access; no dummy device response was used.");
        return 0;
    }
    return 1;
}
