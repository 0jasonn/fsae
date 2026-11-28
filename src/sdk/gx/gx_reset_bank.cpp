#include "sdk/gx/gx_vramcnt.h"

// Clears one bank record, maps its banks back to the LCDC and returns them.
u32 resetBankForX_(u16 *bank) {
    u32 old = *bank;
    *bank = 0;
    data_02129864[0] |= (u16)old;
    GX_VRAMCNT_SetLCDC_(old);
    return old;
}
