#include "engine/functions.h"
#include "knife/comm/wm_connect_callbacks.h"

// WirelessManager::callback_WM_StartMP(void*) (0x02093930): a failed result check gives connect phase 5, an error code of 1
// phase 5 with timer -999. When the MP session is up (kind 10, no error) it starts the data sharing for the players
// (mask (1 << (player count word at 0x1b0 + 1)) - 1, length from 0x1cd4) and moves to phase 1 with the timer counting up, or
// to phase 5 with timer -999 when the call fails.
void Knife_Comm_WirelessManager_callback_WM_StartMP(void *result) {
    WirelessManagerWork *wm;
    WmStartMPResult *cb = (WmStartMPResult *)result;
    s32 code;

    wm = (WirelessManagerWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        wm->connectPhase = 5;
        return;
    }
    if (cb->errCode == 1) {
        wm->connectPhase = 5;
        wm->timer = -999;
        return;
    }
    if (cb->kind == 10 && cb->errCode == 0) {
        code = WM_StartDataSharing((u8 *)wm + 0x1e0, 0xc, (1 << (WM_FIELD(wm, 0x1b0, u16) + 1)) - 1, wm->timer2, 1);
        if (Knife_Comm_WirelessManager_handleResult(wm, code, 0, data_0211b284)) {
            wm->connectPhase = 1;
            wm->timer = wm->timer + 1;
        } else {
            wm->connectPhase = 5;
            wm->timer = -999;
        }
    }
}
