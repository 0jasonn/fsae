#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_string.h"

// STD_CompareString(a, b) (0x0201d9f0): strcmp. When both strings have the same alignment it compares a word at a time
// until a differing word or a word with a zero byte, then finishes byte by byte.
s32 STD_CompareString(const char *a, const char *b) {
    u32 offsetA = (u32)a & 3;
    u32 offsetB = (u32)b & 3;
    u32 charA;
    u32 charB;
    s32 i;
    u32 wordA;
    u32 wordB;

    i = 0;
    if (!(offsetA ^ offsetB)) {
        if (offsetA != 0 && offsetA < 4) {
            do {
                charA = (u8)a[i];
                charB = (u8)b[i];
                if (charA != charB || charA == 0) {
                    return charA - charB;
                }
                i++;
            } while (i + offsetA < 4);
        }
        while (TRUE) {
            wordA = *(const u32 *)(a + i);
            wordB = *(const u32 *)(b + i);
            if (wordA != wordB) {
                break;
            }
            if (~(((wordA & 0x7f7f7f7f) + 0x7f7f7f7f) | wordA | 0x7f7f7f7f)) {
                break;
            }
            i += 4;
        }
    }
    while (TRUE) {
        charA = (u8)a[i];
        charB = (u8)b[i];
        if (charA != charB || charA == 0) {
            return charA - charB;
        }
        i++;
    }
}
