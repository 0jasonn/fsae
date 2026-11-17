#include "engine/functions.h"
#include "knife/comm/wirelessmgr.h"
#include "knife/comm/wm_measure_api.h"
#include "knife/comm/wireless_manager.h"
#include "knife/comm/wireless_scan.h"

// Knife::Comm::WirelessManager::update_scan() (0x02092ad8): state 5 (scanning). Unless a scan call is pending (timer 1) it
// takes the largest field_c8 of the 16 parent entries, then either ends the scan (when requestEndScan set the flag; state 6)
// or starts the next one with WM_StartScanEx (state 5, timer 1). A failing call resets the manager.
void Knife_Comm_WirelessManager_update_scan(void *self) {
    WirelessManagerWork *wm = (WirelessManagerWork *)self;
    s32 i;
    s32 code;

    if (wm->timer == 1) {
        return;
    }
    wm->maxLevel = i = 0;
    for (; i < 16; i++) {
        if (wm->maxLevel < wm->parents[i].field_c8) {
            wm->maxLevel = wm->parents[i].field_c8;
        }
    }
    i = 0;
    if (wm->endScanRequest != 0) {
        wm->endScanRequest = i;
        code = WM_EndScan((void *)Knife_Comm_WirelessManager_callback_WM_StepTimer);
        if (!Knife_Comm_WirelessManager_handleResult(self, code, i, data_0211b1cc)) {
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        }
        wm->state = 6;
        wm->callPending = 1;
        wm->timer = i;
    } else {
        code = WM_StartScanEx((void *)Knife_Comm_WirelessManager_callback_WM_StartScanEx, &wm->scanParam);
        if (!Knife_Comm_WirelessManager_handleResult(self, code, i, data_0211b1d8)) {
            Knife_Comm_WirelessManager_internalReset(self);
            return;
        }
        wm->state = 5;
        wm->timer = 1;
        wm->callPending = i;
    }
}
