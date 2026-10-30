#include "engine/functions.h"
#include "global.h"
#include "types.h"

// VRAM bank state at data_02129864: the bank bits at +0 and the mask saved by the last call at +0x12.
typedef struct VramGroupState {
    u16 bits;
    u8 unk_02[0x10];
    u16 savedMask;           // 0x12
} VramGroupState;

extern VramGroupState data_02129864;

extern "C" void GX_VRAMCNT_SetLCDC_(u16 bits);

// Vram_SetBankGroupA(mask) (0x02015084): the bits are rebuilt from the saved mask and mask is stored there. Mask 0x180
// writes 0x81 to 0x04000249 and then 0x81 to 0x04000248, mask 0x80 writes 0x81 to 0x04000248, mask 4 writes 0x84 to
// 0x04000242. Then the LCDC bank setup runs with the new bits.
extern "C" void Vram_SetBankGroupA(s32 mask);

ARM void Vram_SetBankGroupA(s32 mask) {
    data_02129864.bits = (data_02129864.bits | data_02129864.savedMask) & ~mask;
    data_02129864.savedMask = mask;
    if (mask <= 0x80) {
        if (mask >= 0x80) {
            goto set248;
        }
        if (mask > 4) {
            goto lcdc;
        }
        if (mask < 0 || mask == 0) {
            goto lcdc;
        }
        if (mask == 4) {
            *(u8 *)0x04000242 = 0x84;
        }
    } else {
        if (mask != 0x180) {
            goto lcdc;
        }
        *(u8 *)0x04000249 = 0x81;
set248:
        *(u8 *)0x04000248 = 0x81;
    }
lcdc:
    GX_VRAMCNT_SetLCDC_(data_02129864.bits);
}
