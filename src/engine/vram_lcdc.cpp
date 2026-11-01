#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/a_extern.h"

// LCDC bank control: ORs the low half of mask into the halfword at data_02129864, then tail-calls
// GX_VRAMCNT_SetLCDC_ (0x02014858) with the same mask.

// 0x0201500c
extern "C" void Vram_SetLcdcBits(u32 mask);
ARM void Vram_SetLcdcBits(u32 mask) {
    data_02129864 |= (u16)mask;
    GX_VRAMCNT_SetLCDC_(mask);
}
