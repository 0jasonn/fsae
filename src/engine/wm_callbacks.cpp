#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// Callbacks of the WirelessManager's SDK calls. Each one takes the WM callback result, gets the manager singleton and
// moves the timer (0x1cd8) or the state according to the error code.

// WirelessManager::callback_WM_EnableStep (0x020932fc): on success the timer counts up, on error it is set to 5.
extern "C" void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_EnableStep(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (((WmCallbackHead *)result)->errCode == 0) {
        wm->timer = wm->timer + 1;
    } else {
        wm->timer = 5;
    }
}

// WirelessManager::callback_WM_ResetStep (0x02093340): on success the timer counts up, on error it is set to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_ResetStep(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_ResetStep(void *result) {
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

// WirelessManager::callback_WM_Enable (0x0209338c): on success stores the allowed channels (WM_GetAllowedChannel); if no
// channel is allowed the timer is set to 5. The timer counts up in both cases.
extern "C" void Knife_Comm_WirelessManager_callback_WM_Enable(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_Enable(void *result) {
    WmDWork *wm;

    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (((WmCallbackHead *)result)->errCode == 0) {
        wm->channelMask = WM_GetAllowedChannel();
        if (wm->channelMask == 0) {
            wm->timer = 5;
        }
        wm->timer = wm->timer + 1;
    } else {
        wm->timer = 5;
    }
}

// WirelessManager::callback_WM_PowerOffStep (0x020933fc): same shape as callback_WM_ResetStep.
extern "C" void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_PowerOffStep(void *result) {
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

// WirelessManager::callback_WM_Reset (0x02093448): by error code: 0 counts the timer up (or sets it to 9999 in state 13),
// 1 sets it to -999, 8 sets it to -1000, anything else terminates the program.
extern "C" void Knife_Comm_WirelessManager_callback_WM_Reset(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_Reset(void *result) {
    WmDWork *wm;
    u16 errCode;

    wm = (WmDWork *)func_020909c8();
    errCode = ((WmCallbackHead *)result)->errCode;
    switch (errCode) {
    case 0:
        if (wm->state == 13) {
            wm->timer = 9999;
            return;
        }
        wm->timer = wm->timer + 1;
        return;
    case 1:
        wm->timer = -999;
        return;
    case 8:
        wm->timer = -1000;
        return;
    default:
        OS_Terminate();
        wm->timer = -999;
        return;
    }
}

// WirelessManager::callback_WM_StartScanEx (0x020934dc, invented name): on a scan result list (state 5) appends each
// BSS description with its link level, then counts the timer up. Error 1 sets the timer to -999; state 4 counts it up.
typedef struct WmScanCallback {
    u16 apiId;              // 0
    u16 errCode;            // 2
    u8 unk_4[4];
    u16 scanState;          // 8: 4 done, 5 list ready
    u8 unk_a[4];
    u16 bssCount;           // 0xe
    void *bssDesc[16];      // 0x10
    u16 linkLevel[16];      // 0x50
} WmScanCallback;

extern "C" void Knife_Comm_WirelessManager_callback_WM_StartScanEx(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StartScanEx(void *result) {
    WmDWork *wm;
    WmScanCallback *scan;
    s32 count;
    s32 i;

    scan = (WmScanCallback *)result;
    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (scan->errCode == 1) {
        wm->timer = -999;
        return;
    }
    if (scan->scanState == 4) {
        wm->timer = wm->timer + 1;
        return;
    }
    if (scan->scanState != 5) {
        return;
    }
    count = scan->bssCount;
    for (i = 0; i < count; i++) {
        Knife_Comm_WirelessManager_appendScanResult(wm, scan->bssDesc[i], scan->linkLevel[i]);
    }
    wm->timer = wm->timer + 1;
}
