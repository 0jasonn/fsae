#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// ChildInfo entries of the WirelessManager (15 entries of 0x28 bytes at 0x1a04).
extern "C" void Knife_Comm_ChildInfo_setup(void *child, u16 aid, const u8 *a, const u8 *b);
extern "C" void Knife_Comm_ChildInfo_cleanup(void *child);

// WM callback result for the child entry events: the event kind at 8, data at 0xa, the entry index at 0x10 and data at 0x14.
typedef struct WmChildCallback {
    u16 apiId;
    u16 errCode;
    u8 unk_4[4];
    u16 kind;
    u8 data1[6];
    u16 index;
    u8 unk_12[2];
    u8 data2[16];
} WmChildCallback;

// WirelessManager::callback_WM_ChildEntry (0x02093690, invented name): an error code 1 sets the timer to -999. Kind 0
// counts the timer up, kind 7 sets up child entry (index - 1) and kinds 9 and 26 clean it up. Other kinds do nothing.
extern "C" void Knife_Comm_WirelessManager_callback_WM_ChildEntry(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_ChildEntry(void *result) {
    WmDWork *wm;
    WmChildCallback *cb;
    s32 kind;

    cb = (WmChildCallback *)result;
    wm = (WmDWork *)func_020909c8();
    if (Knife_Comm_WirelessManager_checkCallbackResult(wm, result) == 0) {
        return;
    }
    if (cb->errCode == 1) {
        wm->timer = -999;
        return;
    }
    kind = cb->kind;
    switch (kind) {
    case 0:
        wm->timer = wm->timer + 1;
        return;
    case 7:
        Knife_Comm_ChildInfo_setup((u8 *)wm + 0x1a04 + (cb->index - 1) * 0x28, cb->index, cb->data1, cb->data2);
        return;
    case 9:
        Knife_Comm_ChildInfo_cleanup((u8 *)wm + 0x1a04 + (cb->index - 1) * 0x28);
        return;
    case 26:
        Knife_Comm_ChildInfo_cleanup((u8 *)wm + 0x1a04 + (cb->index - 1) * 0x28);
        return;
    default:
        return;
    }
}

// WirelessManager callback at 0x0209377c (invented name): on success the timer counts up, on error it is set to -999.
extern "C" void Knife_Comm_WirelessManager_callback_WM_StepTimer3(void *result);
ARM void Knife_Comm_WirelessManager_callback_WM_StepTimer3(void *result) {
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
