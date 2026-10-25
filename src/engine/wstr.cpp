#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Length of a NUL-terminated halfword string (not counting the terminator).
extern "C" u32 Wstr_Length(const u16 *str);

ARM u32 Wstr_Length(const u16 *str) {
    u32 length;

    length = -1;
    do {
        length++;
    } while (*str++ != 0);
    return length;
}
