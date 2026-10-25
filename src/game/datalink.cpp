#include "engine/functions.h"
#include "global.h"
#include "game/datalink.h"

// Functions in this file (original names from the debug build):
//   Datalink::verify(void const*, unsigned long) (0x020a6278), Datalink::crc(void const*, unsigned long) (0x020a6304)

extern "C" s32 Mem_Compare(const void *a, const void *b, u32 size); // compares size bytes, zero when equal
extern const u8 data_02124a80[]; // magic of a datalink block

// Datalink::verify(void const*, unsigned long) (0x020a6278): checks the magic, the version, the size, the item count and the CRC
ARM BOOL Datalink::verify(const void *data, u32 size) {
    const u8 *block = (const u8 *)data;

    if (block == NULL) {
        return FALSE;
    }
    if (Mem_Compare(block, data_02124a80, 4) != 0) {
        return FALSE;
    }
    if (block[4] != 1) {
        return FALSE;
    }
    if (block[5] != 1) {
        return FALSE;
    }
    if (*(u32 *)(block + 8) != size) {
        return FALSE;
    }
    return *(u16 *)(block + 0xc) == crc(block + 0x10 + (*(u16 *)(block + 6) << 3), size - 0x10 - (*(u16 *)(block + 6) << 3));
}

// Datalink::crc(void const*, unsigned long) (0x020a6304): CRC-16 (reflected polynomial 0x8408), inverted at the end
ARM u16 Datalink::crc(const void *data, u32 size) {
    const u8 *bytes = (const u8 *)data;
    u32 value = 0xffff;
    u32 i;
    s32 bit;

    for (i = 0; i < size; i++) {
        value ^= bytes[i];
        for (bit = 0; bit < 8; bit++) {
            if (value & 1) {
                value = (value >> 1) ^ 0x8408;
            } else {
                value = value >> 1;
            }
        }
    }
    return (u16)(value ^ 0xffff);
}
