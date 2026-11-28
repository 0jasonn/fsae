#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"

// Maps the VRAM banks in mask to the main OBJ (TwlSDK GX_SetBankForOBJ). The banks that were on the LCDC or on the OBJ
// before are released first. Each case programs the VRAMCNT registers of the banks of the combination: 0x82 = enable,
// MST 2, offset 0; 0x8a, 0x92, 0x9a = the same with offset 1, 2, 3.
void GX_SetBankForOBJ(s32 mask) {
    volatile u8 *vramcntA = (volatile u8 *)0x4000240;
    volatile u8 *vramcntB = (volatile u8 *)0x4000241;
    volatile u8 *vramcntE = (volatile u8 *)0x4000244;
    volatile u8 *vramcntF = (volatile u8 *)0x4000245;
    volatile u8 *vramcntG = (volatile u8 *)0x4000246;

    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_OBJ]) & ~mask;
    data_02129864[GX_VRAM_OBJ] = mask;
    switch (mask) {
    case 0:
        break;
    case 3:
        *vramcntB = 0x8a;
    case 1:
        *vramcntA = 0x82;
        break;
    case 2:
        *vramcntB = 0x82;
        break;
    case 0x70:
        *vramcntG = 0x9a;
    case 0x30:
        *vramcntF = 0x92;
    case 0x10:
        *vramcntE = 0x82;
        break;
    case 0x50:
        *vramcntG = 0x92;
        *vramcntE = 0x82;
        break;
    case 0x60:
        *vramcntG = 0x8a;
    case 0x20:
        *vramcntF = 0x82;
        break;
    case 0x40:
        *vramcntG = 0x82;
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
