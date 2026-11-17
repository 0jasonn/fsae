#include "engine/functions.h"
#include "knife/comm/wm_connect_callbacks.h"

// WirelessManager::callback_WM_StartConnect(void*) (0x020937c8): sets the connect phase (+0x1ce4) and the timer (+0x1cd8) from
// the event kind of the WM_StartConnect result. A failed result check gives phase 5, an error code of 1 phase 5 with
// timer -999. Kind 6 maps error 11 to phase 3 and error 12 to phase 2 (both with timer -999), kind 7 counts the timer up,
// kind 9 gives phase 3 for a parameter of 0x13 and phase 4 otherwise (timer -999), kind 0x1a gives phase 4.
void Knife_Comm_WirelessManager_callback_WM_StartConnect(void *result) {
    WirelessManagerWork *wm;
    WmConnectResult *cb = (WmConnectResult *)result;

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
    switch (cb->kind) {
    case 6:
        switch (cb->errCode) {
        case 0:
            return;
        case 11:
            wm->connectPhase = 3;
            wm->timer = -999;
            return;
        case 12:
            wm->connectPhase = 2;
            wm->timer = -999;
            return;
        }
        return;
    case 7:
        wm->timer = wm->timer + 1;
        return;
    case 9:
        if (cb->param == 0x13) {
            wm->connectPhase = 3;
        } else {
            wm->connectPhase = 4;
        }
        wm->timer = -999;
        return;
    case 26:
        wm->connectPhase = 4;
        return;
    default:
        return;
    }
}
