#include "engine/functions.h"
#include "knife/comm/wireless_manager_methods.h"
#include "knife/comm/wireless_scan.h"

extern "C" {
u32 WM_SetEntry(void *callback, BOOL flag);
void Knife_Comm_WirelessManager_callback_WM_SetEntry(void *result);
BOOL Knife_Comm_WirelessManager_setEntry(void *self, BOOL flag);
}

// Knife::Comm::WirelessManager::setEntry(bool) (0x02091d84): only as a parent (state 8) while no call is pending. Stores the
// flag (+0x1ccc), starts WM_SetEntry and on success sets the pending-call flag (+0x1cdc). Runs with interrupts disabled.
BOOL Knife_Comm_WirelessManager_setEntry(void *self, BOOL flag) {
    WmInterruptSection section;
    WirelessManagerWork *wm = (WirelessManagerWork *)self;

    if (wm->state != 8) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    wm->entryFlag = flag;
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_SetEntry((void *)Knife_Comm_WirelessManager_callback_WM_SetEntry, flag), 0, data_0211b180)) {
        return FALSE;
    }
    wm->callPending = 1;
    return TRUE;
}
