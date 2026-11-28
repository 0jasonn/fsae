#include "sdk/gx/gx_vramcnt.h"
#include "sdk/os/os_vram_exclusive.h"

// Locks the banks in OSi_TryLockVram and maps them to the LCDC.
u32 GX_TrySetBankForLCDC(u32 banks) {
    if (!OSi_TryLockVram((u16)banks, data_02129826)) {
        return 0;
    }
    data_02129864[0] |= (u16)banks;
    GX_VRAMCNT_SetLCDC_(banks);
    return 1;
}
