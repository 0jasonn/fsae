#include "engine/functions.h"
#include "global.h"
#include "types.h"

// VRAM bank state at data_02129864: the bank bits at +0, and the saved masks of the bank groups at +0x14 (group A), +0x16
// (group B) and +0x18 (group C).
typedef struct VramBankState {
    u16 bits;
    u8 unk_02[0x12];
    u16 savedA;
    u16 savedB;
    u16 savedC;
} VramBankState;

extern VramBankState data_02129864;

extern "C" void GX_VRAMCNT_SetLCDC_(u16 bits);
extern "C" void Vram_SetBankGroupB(u32 mask);
extern "C" void Vram_SetBankGroupC(u32 mask);

// Vram_SetBankGroupB(mask) (0x02015190): the group B bits are rebuilt from the saved mask at +0x16 and mask is stored
// there. Mask 0x80 sets bit 0x40000000 of the register at 0x04001000 and writes 0x82 to 0x04000248; mask 0 clears it.
// Then the LCDC bank setup runs with the new bits.
ARM void Vram_SetBankGroupB(u32 mask) {
    data_02129864.bits = (data_02129864.bits | data_02129864.savedB) & ~mask;
    data_02129864.savedB = mask;
    if (mask != 0) {
        if (mask == 0x80) {
            *(volatile u32 *)0x04001000 |= 0x40000000;
            *(u8 *)0x04000248 = 0x82;
        }
    } else {
        *(volatile u32 *)0x04001000 &= ~0x40000000;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864.bits);
}

// Vram_SetBankGroupC(mask) (0x02015210): as Vram_SetBankGroupB with the saved mask at +0x18. Mask 0x100 sets bit
// 0x80000000 of the register at 0x04001000 and writes 0x83 to 0x04000249; mask 0 clears it.
ARM void Vram_SetBankGroupC(u32 mask) {
    data_02129864.bits = (data_02129864.bits | data_02129864.savedC) & ~mask;
    data_02129864.savedC = mask;
    if (mask != 0) {
        if (mask == 0x100) {
            *(volatile u32 *)0x04001000 |= 0x80000000;
            *(u8 *)0x04000249 = 0x83;
        }
    } else {
        *(volatile u32 *)0x04001000 &= ~0x80000000;
    }
    GX_VRAMCNT_SetLCDC_(data_02129864.bits);
}
