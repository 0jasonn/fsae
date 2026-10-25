#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// WirelessManager::requestEndScan (0x02091464, no original name): a leaf function (no interrupt object; REG_IME is
// saved and restored directly). While scanning (state 5) sets the end-of-scan flag at 0xcb9 and returns TRUE.
extern "C" BOOL Knife_Comm_WirelessManager_requestEndScan(void *self);
ARM BOOL Knife_Comm_WirelessManager_requestEndScan(void *self) {
    u16 savedIme;
    WirelessManagerWork *wm;

    savedIme = WM_REG_IME;
    WM_REG_IME = 0;
    wm = (WirelessManagerWork *)self;
    if (wm->state != 5) {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
        return FALSE;
    }
    WM_FIELD(self, 0x1cb9, u8) = 1;
    (void)WM_REG_IME;
    WM_REG_IME = savedIme;
    return TRUE;
}
