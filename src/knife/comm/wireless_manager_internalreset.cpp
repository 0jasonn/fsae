#include "knife/comm/wireless_manager_c.h"

// Knife::Comm::WirelessManager::internalReset() (0x02092820): resets the manager back to an idle state. When the
// state is already below 2 it terminates; otherwise it ends any sharing session and resets through the SDK, then
// moves to state 0xd.

BOOL Knife_Comm_WirelessManager_internalReset(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    wm->unk_1cdc = 0;
    if (wm->state < 2) {
        OS_Terminate();
        wm->state = 0xe;
        wm->timer = 0;
        return FALSE;
    }
    if (wm->state == 8 || wm->state == 0xb) {
        WM_EndDataSharing((u8 *)self + 0x1e0);
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_Reset(Knife_Comm_WirelessManager_callback_WM_Reset), 0, data_0211b19c)) {
        wm->state = 0xe;
        wm->timer = 0;
        return FALSE;
    }
    wm->state = 0xd;
    wm->timer = 0;
    wm->unk_1cdc = 1;
    return TRUE;
}
