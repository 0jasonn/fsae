#include "Unknown/Player.h"
#include "global.h"

extern u8 data_0212c5bc[];
extern u16 data_0216fd04[];
extern u16 data_02170104[];
extern s32 data_0216fcf8[];

ARM void func_02050840(Entity *e) {
    if (data_0212c5bc[0x12] != 0) {
        e->subAction = 6;
    }
    if (data_0212ceb0[e->type2].unk_03[2] == 0) {
        e->subAction = 6;
    }
}

ARM void func_02050880(s32 a, s32 b) {
    u8 row;
    u8 col;
    u16 *src = data_0216fd04;
    u16 *dst = data_02170104;
    s32 tint = (a << 3) * b;
    s32 w = 0x100 - b;
    for (row = 0; row < 0x20; row++) {
        col = 0x10;
        do {
            u32 p = *src++;
            u32 r = ((p & 0x1f) << 3) * w + tint;
            u32 g = (((p >> 5) & 0x1f) << 3) * w + tint;
            u32 bl = (((p >> 10) & 0x1f) << 3) * w + tint;
            *dst++ = (r >> 11) | ((g >> 11) << 5) | ((bl >> 11) << 10);
        } while (--col != 0);
    }
}
