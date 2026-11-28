#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/vram_bank_bits_api.h"
#include "sdk/gx/gx_vramcnt.h"

// Vram_SetBankGroupB(mask) (0x02015190): the LCDC bits get back the old sub BG extended palette banks
// (GX_VRAM_SUB_BGEXTPLTT) minus mask, and mask is stored there. Mask 0x80 sets bit 0x40000000 of the register at
// 0x04001000 and writes 0x82 to 0x04000248; mask 0 clears it. Then the LCDC bank setup runs with the new bits.
void Vram_SetBankGroupB(u32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_SUB_BGEXTPLTT]) & ~mask;
    data_02129864[GX_VRAM_SUB_BGEXTPLTT] = mask;
    if (mask != 0) {
        if (mask == 0x80) {
            *(volatile u32 *)0x04001000 |= 0x40000000;
            *(u8 *)0x04000248 = 0x82;
        }
    } else {
        *(volatile u32 *)0x04001000 &= ~0x40000000;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}

// Vram_SetBankGroupC(mask) (0x02015210): as Vram_SetBankGroupB for the sub OBJ extended palette
// (GX_VRAM_SUB_OBJEXTPLTT). Mask 0x100 sets bit 0x80000000 of the register at 0x04001000 and writes 0x83 to
// 0x04000249; mask 0 clears it.
void Vram_SetBankGroupC(u32 mask) {
    data_02129864[GX_VRAM_LCDC] = (data_02129864[GX_VRAM_LCDC] | data_02129864[GX_VRAM_SUB_OBJEXTPLTT]) & ~mask;
    data_02129864[GX_VRAM_SUB_OBJEXTPLTT] = mask;
    if (mask != 0) {
        if (mask == 0x100) {
            *(volatile u32 *)0x04001000 |= 0x80000000;
            *(u8 *)0x04000249 = 0x83;
        }
    } else {
        *(volatile u32 *)0x04001000 &= ~0x80000000;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864[GX_VRAM_LCDC]);
}
