#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"

// Maps bank F or G to the main OBJ extended palette (TwlSDK GX_SetBankForOBJExtPltt) and turns the main DISPCNT
// extended palette bit on, or off when mask is 0.
void GX_SetBankForOBJExtPltt(s32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_OBJEXTPLTT]) & ~mask;
    data_02129864[GX_VRAM_OBJEXTPLTT] = mask;
    switch (mask) {
    case 0x20:
        *(volatile u32 *)0x4000000 |= 0x80000000;
        *(volatile u8 *)0x4000245 = 0x85;
        break;
    case 0x40:
        *(volatile u32 *)0x4000000 |= 0x80000000;
        *(volatile u8 *)0x4000246 = 0x85;
        break;
    case 0:
        *(volatile u32 *)0x4000000 &= ~0x80000000;
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
