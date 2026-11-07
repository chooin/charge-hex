/*
 * Manually reconstructed from stm32_fw.hex, ARM Thumb instructions.
 * Board photo identifies Geehy APM32F030C8T6 (Cortex-M0+), 8 MHz crystal.
 * STM32F0 register names below are compatibility labels, not vendor identity.
 * This is an analysis translation, NOT recovered original source and NOT a
 * complete flashable firmware. Names below are analyst-assigned. Hardware
 * addresses and firmware function addresses are preserved for cross-checking.
 *
 * External f_XXXXXXXX declarations identify routines whose bodies belong to
 * other modules. cpu_* operations describe exact assembly operations and must
 * be implemented in a dedicated assembly trampoline for a real firmware port.
 */
#include <stdint.h>
#include <stddef.h>
#define U8(a)  (*(volatile uint8_t *)(uintptr_t)(a))
#define U16(a) (*(volatile uint16_t *)(uintptr_t)(a))
#define U32(a) (*(volatile uint32_t *)(uintptr_t)(a))

extern void cpu_disable_irq(void); /* CPSID i */
extern void cpu_enable_irq(void);  /* CPSIE i */
extern void cpu_load_msp_and_blx(uint32_t sp, uint32_t thumb_entry);
extern void f_08001038(void); /* HAL_Init-like: FLASH prefetch and HAL tick */
extern void f_080024c4(void); /* oscillator / bus / peripheral clock setup */
extern void f_0800215c(void); /* GPIO clocks and PB0 input configuration */
extern void f_08002134(void); /* DMA clock and IRQ 10 setup */
extern void f_080021b4(void); /* I2C1 init, handle 0x20000850 */
extern void f_0800220c(void); /* USART1 init, handle 0x20000ba0 */
extern void f_0800175c(void *handle, void *buffer, uint16_t size);
extern void f_080017e0(void *handle);
extern void f_08002314(void); /* update receive procedure, not translated here */
extern void f_080029f8(void *buffer, uint16_t size);
extern void f_08000f8c(void *handle); /* I2C1 MSP deinit: clock and PB6/PB7 */
extern void f_08001ad8(void *handle); /* UART cleanup */
extern void f_0800042c(uint32_t address, const void *data, uint32_t halfwords);
extern void f_08001cb8(void *handle, const void *data, uint16_t size, uint32_t timeout);

/* 0x08002cd4 / 0x08009630: identical scatter-loading copy helpers. */
static void scatter_copy(const uint32_t *source, uint32_t *destination, uint32_t bytes)
{
    while (bytes != 0) {
        *destination++ = *source++;
        bytes -= 4;
    }
}
/* 0x08002ce4 / 0x08009640: scatter-loading zero helper. */
static void scatter_zero(uint32_t *destination, uint32_t bytes)
{
    while (bytes != 0) {
        *destination++ = 0;
        bytes -= 4;
    }
}

/* 0x080001d8, table 0x08002ed4..0x08002ef4. */
void reconstructed_boot_runtime_init(void)
{
    scatter_copy((const uint32_t *)0x08002ef4, (uint32_t *)0x20000000, 0x28);
    scatter_zero((uint32_t *)0x20000028, 0x1060);
    /* Real reset chain sets SP=0x20001088, then branches to 0x08002cf4. */
}
/* 0x08004530, table 0x0800ce78..0x0800ce98. */
void reconstructed_app_runtime_init(void)
{
    scatter_copy((const uint32_t *)0x0800ce98, (uint32_t *)0x200000b4, 0x90);
    scatter_zero((uint32_t *)0x20000144, 0x153c);
    /* Real reset chain sets SP=0x20001680, then branches to 0x0800a708. */
}

/* 0x0800a708..0x0800a740: first operations in application main. */
void reconstructed_app_vector_remap(void)
{
    for (uint32_t i = 0; i < 45; ++i)
        U32(0x20000000 + 4*i) = U32(0x08004000 + 4*i);
    U32(0x40021018) |= 1; /* RCC APB2ENR: SYSCFG clock */
    (void)(U32(0x40021018) & 1); /* clock-enable readback */
    U32(0x40010000) &= ~3u; /* SYSCFG CFGR1 MEM_MODE */
    U32(0x40010000) |= 3u; /* map SRAM at address zero */
}

/* 0x08000280: install default boot metadata if complement pair is invalid.
 * Count argument to flash writer is in halfwords. Marker at F802 is separate.
 */
void reconstructed_boot_metadata_init(void)
{
    uint16_t magic = U16(0x0800f800);
    uint16_t inverse = U16(0x0800f828);
    if (magic == (uint16_t)(inverse ^ 0xffffu))
        return;
    const char filename[8] = "app.bin";
    const uint32_t zero = 0;
    magic = 0x3ec9;
    inverse = 0xc136;
    f_0800042c(0x0800f804, filename, 4);
    f_0800042c(0x0800f824, &zero, 2);
    f_0800042c(0x0800f800, &magic, 1);
    f_0800042c(0x0800f828, &inverse, 1);
}

/* 0x08002494: SysTick handler. HAL tick increment routine is 0x08001028.
 * Initial tick increment (20000018)=1, SystemCoreClock (20000024)=8000000.
 * Clock initialization later changes the core clock/tick reload.
 */
void reconstructed_boot_systick(void)
{
    U32(0x20000020) += U8(0x20000018);
    uint32_t now = U32(0x20000020);
    if ((uint32_t)(now - U32(0x20000014)) >= 1000) {
        U32(0x20000014) = U32(0x20000020);
        U32(0x20000010) += 1; /* software seconds counter */
    }
}

/* 0x08002a68: frame construction, exact byte order and XOR coverage. */
void reconstructed_boot_send(uint8_t start, uint8_t command,
                             const uint8_t *payload, uint8_t length)
{
    volatile uint8_t *frame = (volatile uint8_t *)0x2000089c;
    frame[0] = start;
    frame[1] = (uint8_t)(length + 3);
    frame[2] = command;
    frame[3] = 1;
    for (uint8_t i = 0; i < length; ++i)
        frame[i + 4] = payload[i];
    frame[length + 4] = 0;
    for (uint8_t i = 1; i < length + 4u; ++i)
        frame[length + 4] ^= frame[i];
    f_08001cb8((void *)0x20000ba0, (const void *)frame, length + 5u, 5000);
}

/* 0x08002e0e..0x08002e48: hand off to application. Original does not check
 * the reset address range or the Thumb bit separately. Preserve that fact.
 */
static void reconstructed_boot_jump_to_app(void)
{
    uint32_t stack = U32(0x08004000);
    if ((stack & 0x2fffc000u) == 0x20000000u) {
        uint32_t reset = U32(0x08004004);
        U32(0x20000008) = reset;
        U32(0x2000000c) = reset;
        U32(0xe000e010) &= ~2u; /* 0x0800174c: disable SysTick interrupt */
        cpu_disable_irq();
        f_08000f8c((void *)0x20000850);
        f_08001ad8((void *)0x20000ba0);
        U32(0xe000e280) = 0xffffffff; /* NVIC clear-pending register */
        cpu_enable_irq();
        /* Actual sequence is MSR MSP,r0; LDR reset; BLX reset.
         * Do not implement this by changing SP in an ordinary C frame. */
        cpu_load_msp_and_blx(U32(0x08004000), U32(0x2000000c));
    }
    for (;;) { /* Original 0x08002e48 loops if invalid image or reset returns. */ }
}

/* 0x08002cf4: bootloader main, all top-level branches translated. */
void reconstructed_boot_main(void)
{
    f_08001038();
    f_080024c4();
    f_0800215c();
    f_08002134();
    f_080021b4();
    f_0800220c();
    f_0800175c((void *)0x20000ba0, (void *)0x2000099c, 512);
    reconstructed_boot_metadata_init();

    /* 0x08000a7c reads GPIO IDR. PB0 low requests boot/update mode. */
    if ((U32(0x48000410) & 1u) == 0 && U16(0x0800f802) != 0xaaaa) {
        const uint16_t update_marker = 0xaaaa;
        f_0800042c(0x0800f802, &update_marker, 1);
    }
    if (U16(0x0800f802) == 0xaaaa) {
        U8(0x20000000) = 6;
        uint32_t previous_seconds = U32(0x20000010);
        const uint32_t started_seconds = previous_seconds;
        for (;;) {
            uint32_t now = U32(0x20000010);
            uint32_t elapsed = now - previous_seconds;
            previous_seconds = now;
            if (elapsed != 0) {
                for (uint8_t i = 0; i < 3; ++i) {
                    uint8_t remaining = U8(0x20000000u + i);
                    if (remaining == 0) continue;
                    if (remaining > elapsed) {
                        U8(0x20000000u + i) = (uint8_t)(remaining - elapsed);
                        continue;
                    }
                    U8(0x20000000u + i) = 0;
                    if (i == 0) { /* 0x08002e96 */
                        const uint8_t payload = 0x18;
                        reconstructed_boot_send(0xaa, 0x3c, &payload, 1);
                        U8(0x20000000) = 10;
                    } else if (i == 1) { /* 0x08002e80 */
                        const uint8_t payload = 0;
                        reconstructed_boot_send(0xaa, 0x3d, &payload, 1);
                        U8(0x20000001) = 35;
                    } else { /* 0x08002eac */
                        const uint8_t payload = U8(0x20000004);
                        reconstructed_boot_send(0xaa, 0x3f, &payload, 1);
                        U8(0x20000002) = 10;
                    }
                }
            }
            if ((uint32_t)(U32(0x20000010) - started_seconds) >= 300)
                break;
            if (U8(0x20000b9e) == 1) {
                f_080029f8((void *)0x2000099c, U16(0x20000b9c));
                U8(0x20000b9e) = 0;
            }
            if (U8(0x20000005) == 1)
                break;
            if (U8(0x20000003) == 1) {
                U8(0x20000003) = 0;
                f_080017e0((void *)0x20000ba0);
                f_08002314();
                f_0800175c((void *)0x20000ba0, (void *)0x2000099c, 512);
            }
        }
    }
    reconstructed_boot_jump_to_app();
}

/* Review note: boot_send preserves original uint8 loop behavior. Observed
 * notification callers send one payload byte; length >=252 can wrap the loop
 * bound/index and is not a supported general-purpose interface. Runtime-init
 * reconstructions above express data initialization, not the tail jump to main. */
