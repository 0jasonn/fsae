#include "knife/comm/wireless_manager_c.h"

// Knife::Comm::WirelessManager::disconnect() (0x02091ba0): disconnects a child session (state 0xb) by stopping
// the data sharing and the MP session, then moves to state 0xc.

BOOL Knife_Comm_WirelessManager_disconnect(void *self) {
    WmInterruptSection section;
    WmCWork *wm = (WmCWork *)self;

    if (wm->state != 0xb) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_EndDataSharing((u8 *)self + 0x1e0), 0, data_0211b160)) {
        return FALSE;
    }
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_EndMP(Knife_Comm_WirelessManager_callback_WM_StepTimer5), 0, data_0211b174)) {
        return FALSE;
    }
    wm->state = 0xc;
    wm->timer = 0;
    wm->unk_1cdc = 1;
    return TRUE;
}
