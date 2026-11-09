#include "knife/comm/wireless_manager_c.h"

// Knife::Comm::WirelessManager::endParent() (0x02091738): ends the parent session (state 8) by stopping the
// data sharing and the MP session, then moves to state 9.

BOOL Knife_Comm_WirelessManager_endParent(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    if (wm->state != 8) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_EndDataSharing((u8 *)self + 0x1e0), 0, data_0211b130)) {
        return FALSE;
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_EndMP(Knife_Comm_WirelessManager_callback_WM_StepTimer5), 0, data_0211b144)) {
        return FALSE;
    }
    wm->state = 9;
    wm->timer = 0;
    wm->unk_1cdc = 1;
    return TRUE;
}
