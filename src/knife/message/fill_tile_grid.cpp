#include "engine/functions.h"

void func_020c6198(u16 *dst, s32 width, s32 height, s32 pitch, s32 tile, s32 palette) {
    u16 paletteBits = (u16)((u32)palette << 12);
    s32 x, y;

    for (y = 0; y < height; ++y) {
        u16 *row = dst;
        for (x = 0; x < width; ++x) {
            *row++ = (u16)(tile++ | paletteBits);
        }
        dst += pitch;
    }
}
