#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/str_api.h"

// Length of a NUL-terminated byte string (not counting the terminator).
u32 Str_Length(const u8 *str) {
    u32 length;

    length = -1;
    do {
        length++;
    } while (*str++ != 0);
    return length;
}
