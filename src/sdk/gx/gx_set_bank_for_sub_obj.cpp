#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"

// Maps the VRAM banks in mask to the sub OBJ (TwlSDK GX_SetBankForSubOBJ): bank D or bank I.
void GX_SetBankForSubOBJ(s32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_SUB_OBJ]) & ~mask;
    data_02129864[GX_VRAM_SUB_OBJ] = mask;
    switch (mask) {
    case 0:
        break;
    case 8:
        *(volatile u8 *)0x4000243 = 0x84;
        break;
    case 0x100:
        *(volatile u8 *)0x4000249 = 0x82;
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
