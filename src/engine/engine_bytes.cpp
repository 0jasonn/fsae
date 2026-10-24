#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Byte copy helper used by the engine (no original name; was CopyBytes). Copies count bytes front to back and
// returns dst.
extern "C" void *CopyBytes(void *dst, const void *src, u32 count);

ARM void *CopyBytes(void *dst, const void *src, u32 count) {
    u8 *out;
    const u8 *in;
    u8 byte;

    out = (u8 *)dst;
    in = (const u8 *)src;
    if (count == 0) {
        return dst;
    }
    do {
        byte = *in++;
        count--;
        *out++ = byte;
    } while (count != 0);
    return dst;
}
