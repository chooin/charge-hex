CC ?= cc
AR ?= ar
PYTHON ?= python3
CFLAGS ?= -std=c11 -O0 -Wall -Wextra -Werror

.PHONY: all verify regenerate
all: build/libfirmware_model.a

build:
	mkdir -p build

build/firmware_model.o: firmware_model.c firmware_model.h | build
	$(CC) $(CFLAGS) -c firmware_model.c -o $@

build/firmware_data.o: firmware_data.c firmware_model.h | build
	$(CC) $(CFLAGS) -c firmware_data.c -o $@

build/libfirmware_model.a: build/firmware_model.o build/firmware_data.o
	$(AR) rcs $@ $^

verify:
	$(PYTHON) verify.py

regenerate:
	$(PYTHON) generate.py

build/demo: demo.c build/libfirmware_model.a
	$(CC) $(CFLAGS) demo.c build/libfirmware_model.a -o $@

.PHONY: demo
demo: build/demo
	./build/demo
