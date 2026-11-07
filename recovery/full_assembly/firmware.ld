/* Address-preserving reconstruction; both original vector tables stay put. */
ENTRY(boot_Reset_Handler)
MEMORY { FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K }
SECTIONS {
  .firmware 0x08000000 : { KEEP(*(.firmware)) } > FLASH
  /DISCARD/ : { *(.ARM.attributes) *(.comment) *(.note*) }
}
ASSERT(SIZEOF(.firmware) == 65536, "Reconstructed Flash image must be exactly 64 KiB")
