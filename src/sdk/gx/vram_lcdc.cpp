#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx_vramcnt.h"

// LCDC bank control: ORs the low half of mask into the LCDC bits (data_02129864[GX_VRAM_LCDC]), then tail-calls
// GX_VRAMCNT_SetLCDC_ (0x02014858) with the same mask.

// 0x0201500c
void Vram_SetLcdcBits(u32 mask) {
    data_02129864[GX_VRAM_LCDC] |= (u16)mask;
    GX_VRAMCNT_SetLCDC_(mask);
}
