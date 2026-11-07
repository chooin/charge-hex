AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
PYTHON = python3
.PHONY: all verify regenerate
all: build/firmware.bin build/firmware.hex
build:
	mkdir -p build
build/firmware.o: firmware.S | build
	$(AS) -mcpu=cortex-m0plus -mthumb $< -o $@
build/firmware.elf: build/firmware.o firmware.ld
	$(LD) -T firmware.ld $< -o $@
build/firmware.bin: build/firmware.elf
	$(OBJCOPY) -O binary $< $@
build/firmware.hex: build/firmware.elf
	$(OBJCOPY) -O ihex $< $@
verify: all
	$(PYTHON) verify.py
regenerate:
	$(PYTHON) generate.py
