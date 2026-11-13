CC ?= cc
AR ?= ar
PYTHON ?= python3
ARM_CC ?= arm-none-eabi-gcc
ARM_AS ?= arm-none-eabi-as
ARM_OBJCOPY ?= arm-none-eabi-objcopy
CPPFLAGS += -Iinclude
CFLAGS ?= -O2
WARNINGS = -std=c11 -Wall -Wextra -Werror -pedantic
CORE = $(sort $(wildcard src/domain/*.c src/protocol/*.c src/services/*.c))
HEADERS = $(wildcard include/charge/*.h)
HOST_OBJECTS = $(patsubst %.c,build/host/%.o,$(CORE))
ARM_SOURCES = $(CORE) platform/apm32/legacy_bridge.c
ARM_OBJECTS = $(patsubst %.c,build/arm/%.o,$(ARM_SOURCES))
ARM_FLAGS = -Os -mcpu=cortex-m0plus -mthumb -ffreestanding -fno-builtin \
  -fno-unwind-tables -fno-asynchronous-unwind-tables -ffunction-sections -fdata-sections
MIGRATION_INPUTS = tools/migration_contract.py platform/apm32/migration.json \
  platform/apm32/legacy_bridge.c platform/apm32/abi_shims.S platform/apm32/firmware.ld \
  ../recovery/full_assembly/instructions.json

.PHONY: all host native test clean check-contract
all: host native
host: build/libcharge.a
native: check-contract build/charge.bin build/charge.hex
check-contract:
	$(PYTHON) tools/migration_contract.py
build/host/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) -MMD -MP -c $< -o $@
build/libcharge.a: $(HOST_OBJECTS)
	$(AR) rcs $@ $^
build/arm/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(ARM_CC) $(CPPFLAGS) $(ARM_FLAGS) $(WARNINGS) -MMD -MP -c $< -o $@
build/legacy.S: tools/prepare_legacy.py ../recovery/full_assembly/firmware.S ../stm32_fw.hex $(MIGRATION_INPUTS)
	$(PYTHON) tools/prepare_legacy.py --output $@
build/legacy.o: build/legacy.S
	$(ARM_AS) -mcpu=cortex-m0plus -mthumb $< -o $@
build/abi_shims.o: platform/apm32/abi_shims.S
	@mkdir -p $(dir $@)
	$(ARM_AS) -mcpu=cortex-m0plus -mthumb $< -o $@
build/charge.elf: $(ARM_OBJECTS) build/legacy.o build/abi_shims.o platform/apm32/firmware.ld | check-contract
	$(ARM_CC) $(ARM_FLAGS) -nostdlib -Wl,-z,noexecstack,--gc-sections,-Map,build/charge.map \
	  -T platform/apm32/firmware.ld $(ARM_OBJECTS) build/legacy.o build/abi_shims.o -o $@
build/charge.bin: build/charge.elf
	$(ARM_OBJCOPY) -O binary $< $@
build/charge.hex: build/charge.elf
	$(ARM_OBJCOPY) -O ihex $< $@
build/test_domain_services: ../tests/test_domain_services.c build/libcharge.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< build/libcharge.a -o $@
build/test_protocol: ../tests/protocol_test.c build/libcharge.a
	$(CC) $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $< build/libcharge.a -o $@
test: build/test_domain_services build/test_protocol
	$(PYTHON) ../tests/check_migration_contract.py
	./build/test_domain_services
	./build/test_protocol
clean:
	rm -rf build
-include $(HOST_OBJECTS:.o=.d) $(ARM_OBJECTS:.o=.d)
