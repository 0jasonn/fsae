#include "Unknown/Player.h"
#include "global.h"

extern u16 data_0216fd04[];
extern u16 data_02170104[];

ARM void func_02050880(s32 a, s32 b) {
    u8 row;
    u16 *src = data_0216fd04;
    u16 *dst = data_02170104;
    u8 col;
    s32 w = 0x100 - b;
    s32 tint = (a << 3) * b;
    for (row = 0; row < 0x20; row++) {
        col = 0x10;
        do {
            u32 p = *src++;
            u32 r8 = (p << 27) >> 24;
            u32 g = p >> 5;
            u32 g8 = (g << 27) >> 24;
            u32 b8 = ((g >> 5) << 27) >> 24;
            u32 r = r8 * w + tint;
            u32 gg = g8 * w + tint;
            u32 bb = b8 * w + tint;
            *dst++ = (r >> 11) | ((gg >> 11) << 5) | ((bb >> 11) << 10);
        } while (--col != 0);
    }
}
