#include "sdk/gx/gx_vramcnt.h"

// Size of a VRAM bank selection, the bank state reset and a population count.
u32 GX_GetSizeOfX_(u32 mask) {
    u32 size = 0;
    if (mask & 0x1) {
        size += 0x20000;
    }
    if (mask & 0x2) {
        size += 0x20000;
    }
    if (mask & 0x4) {
        size += 0x20000;
    }
    if (mask & 0x8) {
        size += 0x20000;
    }
    if (mask & 0x10) {
        size += 0x10000;
    }
    if (mask & 0x20) {
        size += 0x4000;
    }
    if (mask & 0x40) {
        size += 0x4000;
    }
    if (mask & 0x80) {
        size += 0x8000;
    }
    if (mask & 0x100) {
        size += 0x4000;
    }
    return size;
}

u32 GX_GetSizeOfARM7(void) {
    return GX_GetSizeOfX_(data_02129864[3]);
}

void GX_InitGXState(void) {
    data_02129864[0] = 0;
    data_02129864[1] = 0;
    data_02129864[2] = 0;
    data_02129864[3] = 0;
    data_02129864[4] = 0;
    data_02129864[5] = 0;
    data_02129864[6] = 0;
    data_02129864[7] = 0;
    data_02129864[8] = 0;
    data_02129864[9] = 0;
    data_02129864[10] = 0;
    data_02129864[11] = 0;
    data_02129864[12] = 0;
    *(volatile u32 *)0x4000240 = 0;
    *(volatile u8 *)0x4000244 = 0;
    *(volatile u8 *)0x4000245 = 0;
    *(volatile u8 *)0x4000246 = 0;
    *(volatile u16 *)0x4000248 = 0;
}

u32 MATH_CountPopulation(u32 x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0f0f0f0f;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0xff;
}
