#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// WirelessManager callback at 0x02093584 (invented name, the same shape as callback_WM_PowerOffStep): on success the timer
// counts up, on error it is set to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_StepTimer(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StepTimer(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (((WmCallbackHead *)result)->errCode == 0) {
        wm->timer = wm->timer + 1;
    } else {
        wm->timer = -999;
    }
}

// WirelessManager::callback_WM_MeasureChannel (0x020935d0): on success keeps the channel with the lowest level so far (in
// bestLevel and bestChannel) and counts the timer up. An error sets the timer to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_MeasureChannel(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_MeasureChannel(void *result) {
    WmDWork *wm;
    WmMeasureResult *measure;

    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    measure = (WmMeasureResult *)result;
    if (measure->errCode == 0) {
        if ((s32)measure->level < wm->bestLevel) {
            wm->bestLevel = measure->level;
            wm->bestChannel = measure->channel;
        }
        wm->timer = wm->timer + 1;
    } else {
        wm->timer = -999;
    }
}

// WirelessManager callback at 0x02093644 (invented name, the same shape as callback_WM_StepTimer).
extern "C" void Knife_Comm_WirelessManager_callback_WM_StepTimer2(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StepTimer2(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (((WmCallbackHead *)result)->errCode == 0) {
        wm->timer = wm->timer + 1;
    } else {
        wm->timer = -999;
    }
}
