#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx_vramcnt.h"

// func_02014c24(mode) (0x02014c24): sets the main BG extended palette banks (TwlSDK GX_SetBankForBGExtPltt). The
// previous banks (GX_VRAM_BGEXTPLTT) go back to the LCDC bits and the new ones are removed; then the display control register (0x04000000) and the LCDC registers (0x04000244..0x04000246)
// are set for the mode. Finally the bank bits are passed to GX_VRAMCNT_SetLCDC_.
void func_02014c24(s32 mode) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_BGEXTPLTT]) & ~mode;
    data_02129864[GX_VRAM_BGEXTPLTT] = mode;
    switch (mode) {
    case 0:
        *(u32 *)0x04000000 &= ~0x40000000;
        break;
    case 0x10:
        *(u32 *)0x04000000 |= 0x40000000;
        *(u8 *)0x04000244 = 0x84;
        break;
    case 0x40:
        *(u32 *)0x04000000 |= 0x40000000;
        *(u8 *)0x04000246 = 0x8c;
        break;
    case 0x60:
        *(u8 *)0x04000246 = 0x8c;
        /* fall through */
    case 0x20:
        *(u8 *)0x04000245 = 0x84;
        *(u32 *)0x04000000 |= 0x40000000;
        break;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
