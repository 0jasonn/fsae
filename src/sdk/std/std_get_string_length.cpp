#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_string.h"

// STD_GetStringLength(str) (0x0201d96c): length of a zero-terminated string; scans a word at a time once aligned (a word
// has no zero byte when the classic bit trick leaves all bits set).
s32 STD_GetStringLength(const char *str) {
    s32 i = 0;
    const u32 *word;
    u32 value;

    if ((u32)str & 3) {
        do {
            if (str[i] == 0) {
                return i;
            }
            i++;
        } while (((u32)(str + i) & 3) != 0);
    }
    word = (const u32 *)(str + i);
    while (TRUE) {
        value = *word;
        if (~(((value & 0x7f7f7f7f) + 0x7f7f7f7f) | value | 0x7f7f7f7f)) {
            break;
        }
        word++;
        i += 4;
    }
    while (str[i] != 0) {
        i++;
    }
    return i;
}
