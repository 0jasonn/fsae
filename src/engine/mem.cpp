#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" s32 Mem_Compare(const u8 *left, const u8 *right, u32 count);
extern "C" void Mem_SetCore(void *dst, s32 value, u32 size);

// Compares count bytes: 0 when equal, -1 when the first differing byte of left is lower, 1 otherwise.
ARM s32 Mem_Compare(const u8 *left, const u8 *right, u32 count) {
    while (count != 0) {
        if (*left++ != *right++) {
            return left[-1] < right[-1] ? -1 : 1;
        }
        count--;
    }
    return 0;
}

// Fills size bytes at dst with value. Short fills go byte by byte; longer ones align dst to 4, write 32-byte
// blocks of the repeated word, then the remaining whole words, then the tail bytes.
ARM void Mem_SetCore(void *dst, s32 value, u32 size) {
    u8 *bytes;
    u32 fill;

    u32 blocks;
    u32 words;
    u32 *wordPtr;

    bytes = (u8 *)dst;
    fill = (u8)value;
    if (size >= 0x20) {
        u32 misalign;
        misalign = (-(u32)bytes) & 3;
        if (misalign != 0) {
            size -= misalign;
            do {
                *bytes++ = fill;
            } while (--misalign != 0);
        }
        if (fill != 0) { fill |= (fill << 24) | (fill << 16) | (fill << 8); }
        wordPtr = (u32 *)bytes;
        for (blocks = size >> 5; blocks != 0; blocks--) {
            wordPtr[0] = fill;
            wordPtr[1] = fill;
            wordPtr[2] = fill;
            wordPtr[3] = fill;
            wordPtr[4] = fill;
            wordPtr[5] = fill;
            wordPtr[6] = fill;
            wordPtr[7] = fill;
            wordPtr += 8;
        }
        for (words = (size & 0x1f) >> 2; words != 0; words--) {
            *wordPtr++ = fill;
        }
        bytes = (u8 *)wordPtr;
        size &= 3;
    }
    while (size != 0) {
        *bytes++ = fill;
        size--;
    }
}
