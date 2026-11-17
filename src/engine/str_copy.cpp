#include "engine/functions.h"

// Copy at most count bytes, pad after a NUL, and return the original destination.
u8 *Str_CopyN(u8 *dst, const u8 *src, u32 count) {
    u8 *out;
    u8 *current;

    out = dst;
    if (count == 0) {
        return dst;
    }
    do {
        current = out;
        *out++ = *src++;
        if (*current == 0) {
            count--;
            while (count != 0) {
                *out++ = 0;
                count--;
            }
            return dst;
        }
        count--;
    } while (count != 0);
    return dst;
}
