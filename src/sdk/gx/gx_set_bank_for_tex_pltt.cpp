#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"

// Maps banks E, F and G to the texture palette (TwlSDK GX_SetBankForTexPltt): 0x83 = enable, MST 3, offset 0; 0x8b,
// 0x93, 0x9b = the same with offset 1, 2, 3.
#pragma optimization_level 2
// Compiled with the SDK's lower optimisation level (no tail merging of the register stores).
#pragma optimization_level 2
void GX_SetBankForTexPltt(s32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_TEXPLTT]) & ~mask;
    data_02129864[GX_VRAM_TEXPLTT] = mask;
    switch (mask) {
    case 0:
        break;
    case 0x60:
        *(volatile u8 *)0x4000246 = 0x8b;
    case 0x20:
        *(volatile u8 *)0x4000245 = 0x83;
        break;
    case 0x70:
        *(volatile u8 *)0x4000246 = 0x9b;
    case 0x30:
        *(volatile u8 *)0x4000245 = 0x93;
    case 0x10:
        *(volatile u8 *)0x4000244 = 0x83;
        break;
    case 0x40:
        *(volatile u8 *)0x4000246 = 0x83;
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
