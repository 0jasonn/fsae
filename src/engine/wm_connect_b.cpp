#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

extern char data_0211b284[];

extern char data_0211b284[];

// WirelessManager callback at 0x020938e4 (invented name): on success the timer counts up, on error it is set to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_StepTimer4(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StepTimer4(void *result) {
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

