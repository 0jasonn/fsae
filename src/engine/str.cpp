#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" u32 Str_Length(const u8 *str);

// Length of a NUL-terminated byte string (not counting the terminator).
ARM u32 Str_Length(const u8 *str) {
    u32 length;

    length = -1;
    do {
        length++;
    } while (*str++ != 0);
    return length;
}
