#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/std/std_string.h"

// STD_CopyString(dst, src) (0x0201d7d0): copies the zero-terminated string including the terminator; returns dst.
char *STD_CopyString(char *dst, const char *src) {
    char *start = dst;

    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst = 0;
    return start;
}
