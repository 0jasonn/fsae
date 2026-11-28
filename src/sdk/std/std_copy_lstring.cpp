#include "global.h"
#include "types.h"
#include "sdk/std/std_string.h"

s32 STD_CopyLString(char *dst, const char *src, s32 size) {
    s32 i = 0;
    const char *cursor = src;
    u32 dstAlign = (u32)dst & 3;
    u32 srcAlign = (u32)src & 3;
    u32 word;

    if ((dstAlign ^ srcAlign) == 0) {
        if (dstAlign != 0) {
            while (i + dstAlign < 4 && i < size - 1) {
                dst[i] = *cursor;
                if (*cursor == 0) {
                    goto finish;
                }
                cursor++;
                i++;
            }
        }
        while (i < size - 4) {
            word = *(u32 *)(src + i);
            if (~(((word & 0x7f7f7f7f) + 0x7f7f7f7f) | word | 0x7f7f7f7f)) {
                break;
            }
            *(u32 *)(dst + i) = word;
            i += 4;
        }
        cursor = src + i;
    }
    while (i < size - 1) {
        dst[i] = *cursor;
        if (*cursor == 0) {
            break;
        }
        i++;
        cursor++;
    }
finish:
    if (i >= size - 1 && size > 0) {
        dst[i] = 0;
    }
    if (*cursor != 0) {
        i += STD_GetStringLength(cursor);
    }
    return i;
}
