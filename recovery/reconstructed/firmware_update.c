/* High-confidence manual translation of boot update routines.
 * Board: Geehy APM32F030C8T6, Cortex-M0+. Not original source or a complete
 * firmware. Untranslated I2C/UART/Flash routines remain external by address.
 * Original error handling and odd-length behavior are preserved intentionally.
 */
#include <stdint.h>
#include <stddef.h>
#define U8(a) (*(volatile uint8_t *)(uintptr_t)(a))

/* Inferred HAL-style signatures, anchored to actual call register/stack use. */
extern int f_08001bb8(void *uart, uint8_t *buffer, uint16_t count, uint32_t timeout);
extern int f_08001d90(uint16_t offset, uint8_t *data, uint16_t length);
extern void f_0800042c(uint32_t address, const void *data, uint32_t halfwords);
extern int f_08002ae8(uint32_t *file_size); /* YMODEM receiver + I2C staging */
extern void f_08000300(uint32_t page_address, uint32_t page_count);
extern void f_08000810(void); /* flash unlock */
extern void f_08000780(void); /* flash lock */
extern int f_08000794(uint32_t program_type, uint32_t address, uint64_t data);

enum { UPDATE_APP_BASE = 0x08004000, UPDATE_METADATA = 0x0800f802 };

/* 0x08002ac4: exact bit recurrence; appended-zero augmentation is in caller. */
uint16_t recovered_update_crc16_step(uint16_t previous, uint8_t byte)
{
    uint32_t crc = previous;
    uint32_t input = (uint32_t)byte + 0x100u;
    do {
        crc <<= 1;
        input <<= 1;
        if ((input & 0x100u) != 0) ++crc;
        if ((crc & 0x10000u) != 0) crc ^= 0x1021u;
    } while ((input & 0x10000u) == 0);
    return (uint16_t)crc;
}
/* 0x080001fc: CRC16/XMODEM equivalent (init 0, no reflection, xorout 0). */
uint16_t recovered_update_crc16(const uint8_t *data, uint32_t length)
{
    uint16_t crc = 0;
    for (uint32_t i = 0; i < length; ++i)
        crc = recovered_update_crc16_step(crc, data[i]);
    crc = recovered_update_crc16_step(crc, 0);
    return recovered_update_crc16_step(crc, 0);
}

/* 0x08002250: UART packet decoder.
 * RAM layout has padding at packet[1]:
 * [0]=SOH/STX; [2]=sequence; [3]=~sequence; [4..]=payload; trailer=CRC high,low.
 * Caller provides >=1030 bytes, as in original buffer at 0x20000448.
 * Returns 0 on accepted packet/EOT/CAN-CAN; 1 on invalid; 2 on 'A'/'a';
 * UART timeout/error return codes otherwise propagate unchanged.
 */
int recovered_update_receive_packet(uint8_t *packet, uint32_t *payload_length,
                                    uint32_t timeout)
{
    uint32_t length = 0;
    uint8_t first;
    *payload_length = 0;
    int status = f_08001bb8((void *)0x20000ba0, &first, 1, timeout);
    if (status == 0) {
        switch (first) {
        case 0x01: length = 128; break;
        case 0x02: length = 1024; break;
        case 0x04: break;
        case 0x18:
            if (f_08001bb8((void *)0x20000ba0, &first, 1, timeout) == 0 && first == 0x18)
                length = 2;
            else
                status = 1;
            break;
        case 0x41:
        case 0x61: status = 2; break;
        default: status = 1; break;
        }
        packet[0] = first;
        if (length >= 128) {
            status = f_08001bb8((void *)0x20000ba0, &packet[2], (uint16_t)(length + 4), timeout);
            if (status == 0) {
                uint16_t supplied_crc = (uint16_t)((uint16_t)packet[length + 4] << 8)
                                      | packet[length + 5];
                if (packet[2] != (uint8_t)(packet[3] ^ 0xffu) ||
                    recovered_update_crc16(&packet[4], length) != supplied_crc) {
                    length = 0;
                    status = 1;
                }
            } else {
                length = 0;
            }
        }
    }
    *payload_length = length;
    return status;
}

/* 0x0800042c: one-page read/modify/erase/program helper.
 * Exact accepted start-address check: address-08004000 < 0000BBFF and even.
 * Original has no check that halfword_count fits the remainder of this page.
 * All observed update-copy callers use aligned pages or metadata-sized writes.
 */
void recovered_flash_write_page_fragment(uint32_t address,
                                        const uint16_t *source, uint32_t halfword_count)
{
    if ((uint32_t)(address - UPDATE_APP_BASE) >= 0xbbffu || (address & 1u) != 0)
        return;
    uint32_t page = address & ~1023u;
    uint32_t halfword_offset = (address & 1023u) >> 1;
    uint16_t *scratch = (uint16_t *)0x20000028;
    const volatile uint16_t *flash = (const volatile uint16_t *)(uintptr_t)page;
    for (uint16_t i = 0; i < 512; ++i)
        scratch[i] = flash[i]; /* 0x08000388 helper in binary */
    for (uint16_t i = 0; i < halfword_count; ++i)
        scratch[halfword_offset + i] = source[i];
    f_08000300(page, 1); /* erase this one 1-KiB page */
    f_08000810();
    for (uint16_t i = 0; i < 512; ++i)
        (void)f_08000794(1, page + 2u*i, scratch[i]);
    f_08000780();
}

/* 0x08002314: receive whole file into I2C staging storage, then commit.
 * f_08002ae8 accepts declared size <= 0xB801. Data packets are staged by
 * f_08001df0 at I2C address 0xA0 (7-bit 0x50), 16-bit offsets, 128-byte pages.
 * The following copy uses declared file size, not the accumulated packet size.
 */
void recovered_update_receive_and_commit(void)
{
    uint32_t file_size = 0;
    int result = f_08002ae8(&file_size);
    uint16_t marker;
    if (result == 0) {
        uint32_t full_pages = file_size >> 10;
        uint16_t remainder = (uint16_t)(file_size & 1023u);
        uint32_t staging_offset = 0;
        uint32_t flash_address = UPDATE_APP_BASE;
        uint8_t *buffer = (uint8_t *)0x20000448;
        for (uint32_t i = 0; i < full_pages; ++i) {
            (void)f_08001d90((uint16_t)staging_offset, buffer, 1024);
            f_0800042c(flash_address, buffer, 512);
            staging_offset += 1024;
            flash_address += 1024;
        }
        if (remainder != 0) {
            (void)f_08001d90((uint16_t)staging_offset, buffer, remainder);
            /* Original rounds down, so the final odd byte is not copied. */
            f_0800042c(flash_address, buffer, (uint16_t)(remainder >> 1));
        }
        uint16_t filename_bytes = 0;
        const uint8_t *filename = (const uint8_t *)0x20000428;
        while (filename_bytes < 32 && filename[filename_bytes] != 0)
            ++filename_bytes;
        if (filename_bytes < 32)
            filename_bytes += (filename_bytes & 1u) ? 1 : 2;
        f_0800042c(UPDATE_METADATA + 2, filename, filename_bytes >> 1);
        f_0800042c(UPDATE_METADATA + 0x22, &file_size, 2);
        marker = 0x5555;
        f_0800042c(UPDATE_METADATA, &marker, 1);
        U8(0x20000004) = 0;
    } else if (result == 2 || result == 4 || result == 5) {
        marker = 0xa5a5;
        f_0800042c(UPDATE_METADATA, &marker, 1);
        U8(0x20000004) = result == 2 ? 6 : (result == 4 ? 5 : 4);
    } else {
        return;
    }
    U8(0x20000002) = 1; /* arm status notification timer, not immediate app jump */
}
