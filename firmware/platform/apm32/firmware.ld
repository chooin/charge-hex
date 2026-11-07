/* Transitional image: original Boot/App addresses plus C extension in App.
 * Metadata/config are preserved. This is not the byte-identical recovery build.
 */
ENTRY(boot_Reset_Handler)
MEMORY {
  LEGACY (rx) : ORIGIN = 0x08000000, LENGTH = 0xd000
  EXTENSION (rx) : ORIGIN = 0x0800d000, LENGTH = 0x2800
  PERSISTENT (r) : ORIGIN = 0x0800f800, LENGTH = 0x800
}
SECTIONS {
  .firmware : { KEEP(*(.firmware)) } > LEGACY
  .extension : {
    *(.text*) *(.rodata*)
    __extension_used_end = .;
    . = ORIGIN(EXTENSION) + LENGTH(EXTENSION);
  } > EXTENSION = 0xff
  .persistent : { KEEP(*(.persistent)) } > PERSISTENT
  .unexpected_ram : { *(.data*) *(.bss*) *(COMMON) } > EXTENSION
  /DISCARD/ : { *(.ARM.attributes) *(.comment) *(.note*) }
}
ASSERT(SIZEOF(.firmware) == 0xd000, "Legacy layout changed")
ASSERT(SIZEOF(.persistent) == 0x800, "Metadata/config layout changed")
ASSERT(SIZEOF(.unexpected_ram) == 0, "New static RAM needs startup integration")
