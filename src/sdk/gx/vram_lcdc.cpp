#include "engine/functions.h"
#include "global.h"
#include "types.h"

// TODO(headers): this declaration of GX_VRAMCNT_SetLCDC_ differs from the shared one;
// see the header restructure report.
extern "C" void GX_VRAMCNT_SetLCDC_(u32 mask);
// TODO(headers): this declaration of data_02129864 differs from the shared one; see the header restructure report.
extern u16 data_02129864;

// LCDC bank control: ORs the low half of mask into the halfword at data_02129864, then tail-calls
// GX_VRAMCNT_SetLCDC_ (0x02014858) with the same mask.

// 0x0201500c
extern "C" void Vram_SetLcdcBits(u32 mask);
void Vram_SetLcdcBits(u32 mask) {
    data_02129864 |= (u16)mask;
    GX_VRAMCNT_SetLCDC_(mask);
}
