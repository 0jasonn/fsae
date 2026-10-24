#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (module cg, original names from the debug build): CgSubTrans (CgSubTrans())

extern u32 data_02134928;   // bit mask of the 0x20-byte blocks to copy (one bit per block)
extern u8 data_021359a0[];  // source blocks, 0x20 bytes each

// CgSubTrans (0x02029eac): copies the 0x20-byte blocks selected by the mask to 0x05000400 and clears the mask.
ARM void CgSubTrans(void) {
    u8 *src;
    u32 dst;
    u32 mask;

    mask = data_02134928;
    src = data_021359a0;
    dst = 0x5000400;
    while (mask != 0) {
        if (mask & 1) {
            MIi_CpuCopyFast(src, (void *)dst, 0x20);
        }
        src += 0x20;
        dst += 0x20;
        mask >>= 1;
    }
    data_02134928 = 0;
}
