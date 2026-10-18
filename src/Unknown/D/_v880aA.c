#include "Unknown/Player.h"
#include "global.h"

extern u16 data_0216fd04[];
extern u16 data_02170104[];

ARM void func_02050880(s32 a, s32 b) {
    u16 *src = data_0216fd04;
    u16 *dst = data_02170104;
    u8 row;
    u8 col;
    s32 tint = (a << 3) * b;
    s32 w = 0x100 - b;
    for (row = 0; row < 0x20; row++) {
        col = 0x10;
        do {
            u32 p = *src++;
            u32 r = ((p << 27) >> 24) * w + tint;
            u32 g = (((p >> 5) << 27) >> 24) * w + tint;
            u32 bl = (((p >> 10) << 27) >> 24) * w + tint;
            *dst++ = (r >> 11) | ((g >> 11) << 5) | ((bl >> 11) << 10);
        } while (--col != 0);
    }
}
