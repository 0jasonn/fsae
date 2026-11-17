#include "engine/functions.h"
#include "knife/comm/wireless_manager_methods.h"

// Knife::Comm::WirelessManager::getConnectResult() const (0x02091cd8): the connect result for the current state, read with
// interrupts off: 0xff while connecting (state 10), 1 once connected (state 11), the connect phase in state 2, else 0.
// The state is read before the interrupt mask is cleared.

extern "C" {
s32 Knife_Comm_WirelessManager_getConnectResult(void *self);
}

s32 Knife_Comm_WirelessManager_getConnectResult(void *self) {
    WmCWork *wm = (WmCWork *)self;
    u16 savedIme = WM_REG_IME;
    s32 state = wm->state;

    WM_REG_IME = 0;
    if (state == 10) {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
        return 0xff;
    }
    if (state == 11) {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
        return 1;
    }
    if (state == 2) {
        (void)WM_REG_IME;
        WM_REG_IME = savedIme;
        return wm->connectPhase;
    }
    (void)WM_REG_IME;
    WM_REG_IME = savedIme;
    return 0;
}
