#include "engine/functions.h"
#include "global.h"

// ConvertDispCntToTWL (0x0202a754): converts the DISPCNT value to the TWL layout: bit 5 moves to bit 23, bit 6 is
// replaced by bit 4, and the bits of flags selected by 0xff7f0068 are added.
u32 ConvertDispCntToTWL(u16 dispCnt, u32 flags) {
    u32 f = flags & 0xff7f0068;
    u32 v = dispCnt & 0xffe7;

    if (v & 0x20) {
        v &= ~0x20;
        v |= 0x800000;
    }
    if (v & 0x40) {
        v &= ~0x40;
        v |= 0x10;
    }
    return v | f;
}
