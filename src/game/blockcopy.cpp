#include "engine/functions.h"
#include "global.h"
// Address -> name: 0x0202a128 BlockCopy.

ARM void BlockCopy(u16 *dst, u16 *src, u16 width, u16 flags) {
    u16 stride;
    u16 i;

    stride = (flags & 0x8000) ? 0x40 - width : 0x20 - width;
    flags &= 0x7fff;
    do {
        for (i = 0; i < width; i++) {
            *dst++ = *src++;
        }
        dst += stride;
        flags--;
    } while (flags != 0);
}
