#include "engine/functions.h"
#include "sdk/gx/gx_vramcnt.h"

#define VRAMCNT_A (*(volatile u8 *)0x4000240)
#define VRAMCNT_B (*(volatile u8 *)0x4000241)
#define VRAMCNT_C (*(volatile u8 *)0x4000242)
#define VRAMCNT_D (*(volatile u8 *)0x4000243)
#define DISP3DCNT (*(volatile u16 *)0x4000060)

// Maps the VRAM banks in mask to the texture image slots (TwlSDK GX_SetBankForTex) and turns the 3D texture mapping
// bit of DISP3DCNT on, or off when mask is 0. 0x83 = enable, MST 3, offset 0; 0x8b, 0x93, 0x9b = offset 1, 2, 3.
void GX_SetBankForTex(s32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_TEX]) & ~mask;
    data_02129864[GX_VRAM_TEX] = mask;
    if (mask == 0) {
        DISP3DCNT &= 0xcffe;
    } else {
        DISP3DCNT = (DISP3DCNT & ~0x3000) | 1;
        switch (mask) {
        case 0:
            break;
        case 5:
            VRAMCNT_A = 0x83;
            VRAMCNT_C = 0x8b;
            break;
        case 9:
            VRAMCNT_A = 0x83;
            VRAMCNT_D = 0x8b;
            break;
        case 10:
            VRAMCNT_B = 0x83;
            VRAMCNT_D = 0x8b;
            break;
        case 11:
            VRAMCNT_A = 0x83;
            VRAMCNT_B = 0x8b;
            VRAMCNT_D = 0x93;
            break;
        case 13:
            VRAMCNT_A = 0x83;
            VRAMCNT_C = 0x8b;
            VRAMCNT_D = 0x93;
            break;
        case 8:
            VRAMCNT_D = 0x83;
            break;
        case 12:
            VRAMCNT_D = 0x8b;
        case 4:
            VRAMCNT_C = 0x83;
            break;
        case 14:
            VRAMCNT_D = 0x93;
        case 6:
            VRAMCNT_C = 0x8b;
        case 2:
            VRAMCNT_B = 0x83;
            break;
        case 15:
            VRAMCNT_D = 0x9b;
        case 7:
            VRAMCNT_C = 0x93;
        case 3:
            VRAMCNT_B = 0x8b;
        case 1:
            VRAMCNT_A = 0x83;
            break;
        }
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
