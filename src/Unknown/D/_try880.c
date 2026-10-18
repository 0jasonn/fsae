#include "Unknown/Player.h"
#include "global.h"

extern u16 data_0216fd04[];
extern u16 data_02170104[];

typedef struct Color15 {
    u16 r : 5;
    u16 g : 5;
    u16 b : 5;
    u16 x : 1;
} Color15;

ARM void func_02050880(s32 a, s32 b) {
    u8 row;
    u8 col;
    Color15 *src = (Color15 *)data_0216fd04;
    Color15 *dst = (Color15 *)data_02170104;
    s32 tint = (a << 3) * b;
    s32 w = 0x100 - b;
    for (row = 0; row < 0x20; row++) {
        col = 0x10;
        do {
            Color15 c = *src++;
            u32 r = (c.r << 3) * w + tint;
            u32 g = (c.g << 3) * w + tint;
            u32 bl = (c.b << 3) * w + tint;
            Color15 o;
            *(u16 *)dst = (r >> 11) | ((g >> 11) << 5) | ((bl >> 11) << 10);
            dst++;
        } while (--col != 0);
    }
}
