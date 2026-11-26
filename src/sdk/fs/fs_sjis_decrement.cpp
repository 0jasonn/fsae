#include "global.h"
#include "types.h"
#include "sdk/fs/fs_api.h"

// Steps back one Shift-JIS character: the lead-byte run before the position decides whether the byte at pos - 1 is a trail byte.

s32 FSi_DecrementSjisPosition(const char *str, s32 pos) {
    s32 i = pos - 1;

    while (i > 0 && (u32)(((u8)str[i - 1] ^ 0x20) - 0xa1) < 0x3c) {
        i--;
    }
    return (pos - 1) - (((pos - 1) - i) & 1);
}
