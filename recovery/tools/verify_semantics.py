#!/usr/bin/env python3
"""Differentially emulate original Thumb and recompiled recovered C; no hardware I/O.

Requires Python unicorn/capstone and arm-none-eabi-{gcc,objcopy,nm}. Build products
live in a temporary directory. GPIO and delay calls are intercepted as observable
call events; their implementations and electrical effects are NOT emulated.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import random
import shutil
import subprocess
import tempfile
import time

import capstone
import unicorn
from unicorn import Uc, UC_ARCH_ARM, UC_MODE_THUMB, UC_MODE_MCLASS, UC_HOOK_CODE
from unicorn.arm_const import (
    UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
    UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
    UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
    UC_ARM_REG_R12, UC_ARM_REG_SP, UC_ARM_REG_LR, UC_ARM_REG_PC,
)

FLASH = 0x08000000
C_FLASH = 0x08100000
SRAM = 0x20000000
RETURN = 0x0801F000
COMPARE_BYTES = 0x3000
REGISTERS = [UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3,
             UC_ARM_REG_R4, UC_ARM_REG_R5, UC_ARM_REG_R6, UC_ARM_REG_R7,
             UC_ARM_REG_R8, UC_ARM_REG_R9, UC_ARM_REG_R10, UC_ARM_REG_R11,
             UC_ARM_REG_R12]


def run(command: list[str]) -> str:
    result = subprocess.run(command, check=True, capture_output=True, text=True)
    return result.stdout


def sha(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class Machine:
    def __init__(self, image: bytes, address: int, hooks: dict[int, tuple[str, int]]):
        self.uc = Uc(UC_ARCH_ARM, UC_MODE_THUMB | UC_MODE_MCLASS)
        self.uc.mem_map(FLASH, 0x20000)
        if address != FLASH:
            self.uc.mem_map(address, (len(image) + 0xFFF) & ~0xFFF)
        self.uc.mem_write(address, image)
        self.uc.mem_map(SRAM, 0x10000)
        self.hooks = hooks
        self.events: list[dict] = []
        self.returned = False
        self.instructions = 0
        self.uc.hook_add(UC_HOOK_CODE, self.on_instruction)

    def on_instruction(self, uc: Uc, address: int, size: int, _data):
        self.instructions += 1
        if address == RETURN:
            self.returned = True
            uc.emu_stop()
        elif address in self.hooks:
            name, argc = self.hooks[address]
            args = [uc.reg_read(r) for r in REGISTERS[:argc]]
            self.events.append({'call': name, 'args': args})
            # Mimic a void leaf return. No physical GPIO or delay is executed.
            uc.reg_write(UC_ARM_REG_PC, uc.reg_read(UC_ARM_REG_LR))

    def call(self, entry: int, memory: bytes, args: list[int]):
        self.uc.mem_write(SRAM, memory)
        self.uc.mem_write(SRAM + 0xE000, bytes(0x2000))
        for index, register in enumerate(REGISTERS):
            self.uc.reg_write(register, 0x33330000 + index)
        for register, value in zip(REGISTERS, args):
            self.uc.reg_write(register, value)
        self.uc.reg_write(UC_ARM_REG_SP, SRAM + 0xF000)
        self.uc.reg_write(UC_ARM_REG_LR, RETURN | 1)
        self.events = []
        self.instructions = 0
        self.returned = False
        self.uc.emu_start(entry | 1, RETURN + 2, count=20000)
        if not self.returned:
            raise RuntimeError(f'No return from {entry:#x}; PC={self.uc.reg_read(UC_ARM_REG_PC):#x}')
        return bytes(self.uc.mem_read(SRAM, COMPARE_BYTES)), self.events, self.instructions


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--seed', type=int, default=0xF030C8)
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    recovery = Path(__file__).resolve().parents[1]
    source = recovery / 'reconstructed/application.c'
    firmware_path = recovery / 'artifacts/firmware.bin'
    output = args.output or recovery / 'artifacts/verification_semantics.json'
    firmware = firmware_path.read_bytes()
    source_hash = sha(source.read_bytes())
    for executable in ('arm-none-eabi-gcc', 'arm-none-eabi-objcopy', 'arm-none-eabi-nm'):
        if shutil.which(executable) is None:
            raise SystemExit(f'Missing tool: {executable}')
    rng = random.Random(args.seed)
    started = time.monotonic()
    function_pairs = [
        ('channel_state', 0x0800C85C, 'recovered_set_channel_state'),
        ('clear_accounting', 0x08009E14, 'recovered_clear_channel_accounting'),
        ('pulse_command', 0x0800CDB8, 'recovered_pulse_command'),
        ('configured_command', 0x0800CDA4, 'recovered_send_configured_command'),
    ]
    with tempfile.TemporaryDirectory(prefix='firmware-semantics-') as directory:
        tmp = Path(directory)
        stubs = tmp / 'stubs.c'
        stubs.write_text('''#include <stdint.h>
void fw_08005d46_gpio_write(uint32_t p, uint16_t pins, uint32_t s) {(void)p;(void)pins;(void)s;}
void fw_0800cc44_delay(uint32_t n) {(void)n;}
void fw_0800cc64_delay(uint32_t n) {(void)n;}
''')
        elf, binary = tmp / 'recovered.elf', tmp / 'recovered.bin'
        command = ['arm-none-eabi-gcc', '-std=c11', '-mcpu=cortex-m0', '-mthumb',
                   '-O2', '-ffreestanding', '-fno-builtin', '-ffunction-sections',
                   '-fdata-sections', '-nostdlib', '-Wl,--gc-sections',
                   '-Wl,-Ttext=0x08100000', '-Wl,-e,recovered_set_channel_state']
        command += ['-Wl,--undefined=' + name for _, _, name in function_pairs]
        command += [str(source), str(stubs), '-o', str(elf)]
        run(command)
        run(['arm-none-eabi-objcopy', '-O', 'binary', str(elf), str(binary)])
        symbols = {}
        for line in run(['arm-none-eabi-nm', '-n', str(elf)]).splitlines():
            fields = line.split()
            if len(fields) == 3:
                symbols[fields[2]] = int(fields[0], 16)
        compiled_image = binary.read_bytes()
        event_hooks = {
            0x08005D46: ('gpio_write', 3),
            0x0800CC44: ('delay_cc44', 1),
            0x0800CC64: ('delay_cc64', 1),
        }
        recovered_hooks = {
            symbols['fw_08005d46_gpio_write']: ('gpio_write', 3),
            symbols['fw_0800cc44_delay']: ('delay_cc44', 1),
            symbols['fw_0800cc64_delay']: ('delay_cc64', 1),
        }
        original = Machine(firmware, FLASH, event_hooks)
        recovered = Machine(compiled_image, C_FLASH, recovered_hooks)
        summaries = {}
        failures = []
        transcript = hashlib.sha256()

        def compare(group: str, original_entry: int, c_name: str, values: list[int], memory: bytes, label: str):
            summary = summaries.setdefault(group, {
                'original_entry': f'{original_entry:#010x}',
                'recovered_function': c_name,
                'recovered_entry': f'{symbols[c_name]:#010x}',
                'cases': 0, 'passed': 0, 'failed': 0,
            })
            summary['cases'] += 1
            first = original.call(original_entry, memory, values)
            second = recovered.call(symbols[c_name], memory, values)
            equal = first[:2] == second[:2]
            summary['passed' if equal else 'failed'] += 1
            transcript.update(json.dumps([group, label, values, sha(memory), sha(first[0]), first[1], equal],
                                         sort_keys=True).encode())
            if not equal:
                differences = [f'{SRAM+i:#010x}' for i, (a, b) in enumerate(zip(first[0], second[0])) if a != b]
                failures.append({'group': group, 'label': label, 'arguments': values,
                                 'memory_differences': differences[:30],
                                 'original_events': first[1], 'recovered_events': second[1]})

        # All uint8 channel inputs include invalid 12..255. Original increments
        # then truncates channel; 255 wraps to switch-default 0 and is a no-op.
        for channel in range(256):
            for enabled in (0, 1, 2, 255):
                for repeat in range(3):
                    memory = rng.randbytes(COMPARE_BYTES)
                    compare(*function_pairs[0], [channel, enabled], memory, f'{channel}/{enabled}/{repeat}')
        # This routine's callers constrain channels; no invented bounds check.
        for channel in range(12):
            for repeat in range(20):
                compare(*function_pairs[1], [channel], rng.randbytes(COMPARE_BYTES), f'{channel}/{repeat}')
        for command_value in range(512):
            for flag in (0, 1, 2):
                memory = bytearray(rng.randbytes(COMPARE_BYTES))
                memory[0x8CC] = flag
                compare(*function_pairs[2], [command_value], bytes(memory), f'{command_value}/{flag}')
        for config in range(256):
            for flag in (0, 1):
                memory = bytearray(rng.randbytes(COMPARE_BYTES))
                memory[0x8CB], memory[0x8CC] = config, flag
                compare(*function_pairs[3], [], bytes(memory), f'{config}/{flag}')

        report = {
            'kind': 'offline-original-vs-recompiled-C-differential-emulation',
            'passed': not failures,
            'firmware_sha256': sha(firmware),
            'application_c_sha256': source_hash,
            'compiled_image_sha256': sha(compiled_image),
            'transcript_sha256': transcript.hexdigest(),
            'seed': args.seed,
            'unicorn_version': unicorn.__version__,
            'capstone_version': capstone.__version__,
            'compiler': run(['arm-none-eabi-gcc', '--version']).splitlines()[0],
            'build_flags': command[1:command.index(str(source))],
            'functions': summaries,
            'total_cases': sum(s['cases'] for s in summaries.values()),
            'failure_count': len(failures),
            'failures': failures[:10],
            'elapsed_seconds': round(time.monotonic() - started, 3),
            'comparison': {
                'memory_range': '0x20000000..0x20002FFF (all bytes)',
                'call_events': 'ordered GPIO port/pins/state and delay routine/argument',
                'hardware_execution': False,
            },
            'limitations': [
                'Finite cases with deterministic random initial SRAM; not a proof for every possible state.',
                'GPIO and delay subroutines are intercepted. Timing, electrical effects, interrupts and devices are not modeled.',
                'Stack scratch bytes and caller-saved registers are excluded; lower SRAM and ordered call events are compared.',
                'Only the four listed functions are validated. Full firmware, parser and main state-machine equivalence remain unverified.',
            ],
        }
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(report, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps({'passed': report['passed'], 'cases': report['total_cases'],
                      'failures': report['failure_count'], 'report': str(output)}, ensure_ascii=False))
    return 0 if report['passed'] else 1


if __name__ == '__main__':
    raise SystemExit(main())
