#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

extern char data_0211b284[];

// WirelessManager callback at 0x02093a1c (invented name): on success the timer counts up, on error it is set to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_StepTimer5(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StepTimer5(void *result) {
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

// WirelessManager::callback_WM_SetEntry (0x02093a68): clears the flag at 0x1cdc, then on success sets the entry word at
// 0x1ae to the manager flag at 0x1ccc; on error sets the flag from the entry word.
extern "C" void Knife_Comm_WirelessManager_callback_WM_SetEntry(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_SetEntry(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    wm->unk_1cdc = 0;
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (((WmCallbackHead *)result)->errCode == 0) {
        if (wm->flag != 0) {
            WM_FIELD(wm, 0x1ae, u16) = 1;
        } else {
            WM_FIELD(wm, 0x1ae, u16) = 0;
        }
        return;
    }
    wm->flag = (WM_FIELD(wm, 0x1ae, u16) != 0);
}

// WirelessManager callback at 0x02093adc (invented name): clears the flag at 0x1cdc and runs the result check.
extern "C" void Knife_Comm_WirelessManager_callback_WM_ClearFlag(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_ClearFlag(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    wm->unk_1cdc = 0;
    (void)Knife_Comm_WirelessManager_checkCallbackResult(wm, result);
}
