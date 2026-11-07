/* Keep the register guarantees used by the original Keil call sites.
 * These entry points receive r0-r3 and SP unchanged from the entry veneer.
 * The implementations below use ordinary AAPCS; legacy callers sometimes
 * retain caller-saved registers across a particular known leaf function.
 *
 * In particular, 08009DDE calls clear_channel and 08009DE2 immediately
 * stores through r3. Merely observing the C function's memory writes is
 * insufficient to verify this boundary.
 *
 * No fifth stack argument is present on these four entry points. Each BL
 * preserves the incoming SP alignment (8 or 16 bytes of temporary stack).
 */
.syntax unified
.cpu cortex-m0plus
.thumb

.macro preserve_r3_entry name
    .section .text.\name,"ax",%progbits
    .balign 2
    .global \name
    .type \name, %function
    .thumb_func
\name:
    push {r3, lr}
    mov r3, ip
    push {r3, r4}
    bl \name\()_impl
    pop {r3, r4}
    mov ip, r3
    pop {r3, pc}
    .size \name, .-\name
.endm

/* Original 08009E14 leaves r3 untouched. */
preserve_r3_entry charge_legacy_clear_channel

/* A register in a PUSH list is not necessarily preserved: these originals
 * reuse the saved r3 slot as scratch. C85C returns the entry packed-status
 * byte on accepted channels; 74C4 returns 50 there (the probe timeout).
 * Their callers do not consume these scratch results. Preserve ip here,
 * without inventing a promise to preserve the incoming r3 value.
 */
.macro preserve_ip_entry name
    .section .text.\name,"ax",%progbits
    .balign 2
    .global \name
    .type \name, %function
    .thumb_func
\name:
    push {r4, lr}
    mov r4, ip
    bl \name\()_impl
    mov ip, r4
    pop {r4, pc}
    .size \name, .-\name
.endm
preserve_ip_entry charge_legacy_set_channel
preserve_ip_entry charge_legacy_storage_wait_ready

/* Original 08007498 preserves r1/r2: its outgoing stack arguments rewrite
 * their slots with the same data pointer and size. The saved r3 slot becomes
 * timeout=1000 on the valid-read path, so r3 is not an invariant.
 */
.section .text.charge_legacy_storage_read,"ax",%progbits
.balign 2
.global charge_legacy_storage_read
.type charge_legacy_storage_read, %function
.thumb_func
charge_legacy_storage_read:
    push {r1, r2, r4, lr}
    mov r4, ip
    bl charge_legacy_storage_read_impl
    mov ip, r4
    pop {r1, r2, r4, pc}
.size charge_legacy_storage_read, .-charge_legacy_storage_read

.section .note.GNU-stack,"",%progbits
