#include "engine/functions.h"
#include "global.h"
#include "types.h"

// LCDC state at data_02129864: the bank bits at +0, the bank mode at +4 and the display mode at +0xe.
typedef struct LcdcBankState {
    u16 bits;
    u8 unk_02[0x02];
    u16 bankMode;
    u8 unk_06[0x08];
    u16 displayMode;
} LcdcBankState;

extern LcdcBankState data_02129864;

extern "C" void GX_VRAMCNT_SetLCDC_(u16 bits);

// func_02014c24(mode) (0x02014c24): the bits of the previous mode are merged into the bank bits and the new mode's
// bits are removed; then the display control register (0x04000000) and the LCDC registers (0x04000244..0x04000246)
// are set for the mode. Finally the bank bits are passed to GX_VRAMCNT_SetLCDC_.
void func_02014c24(s32 mode) {
    data_02129864.bits = (data_02129864.bits | data_02129864.displayMode) & ~mode;
    data_02129864.displayMode = mode;
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
    GX_VRAMCNT_SetLCDC_(data_02129864.bits);
}
