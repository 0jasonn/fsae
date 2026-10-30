#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// Knife::Comm::WirelessManager state helpers. Each one saves REG_IME, clears it, reads the state at 0x1cc4 and restores
// REG_IME before returning. The state values used here: 8 (parent) and 11 (child).

// WirelessManager::getParentFlag (0x02091e7c, invented name): the byte at 0x1ccc while the state is 8, otherwise 0.
extern "C" u8 Knife_Comm_WirelessManager_getParentFlag(void *self);
ARM u8 Knife_Comm_WirelessManager_getParentFlag(void *self) {
    u16 savedIme;
    s32 state;
    u8 flag;

    savedIme = WM_REG_IME;
    state = WM_FIELD(self, 0x1cc4, s32);
    WM_REG_IME = 0;
    if (state != 8) {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
        return 0;
    }
    (void)WM_REG_IME;
    flag = WM_FIELD(self, 0x1ccc, u8);
    WM_REG_IME = savedIme;
    return flag;
}
