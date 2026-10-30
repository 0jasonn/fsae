#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wm_d.h"

// WirelessManager::handleResult (0x02092758): handles the result of a WM call with code (the WM status) and flag. Codes
// 3, 4 and 6 reset the manager (internalReset), code 8 moves the state to 15 with the timer cleared, code 1 resets only
// when flag is set. Returns TRUE for any other code.
extern "C" BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name);
ARM BOOL Knife_Comm_WirelessManager_handleResult(void *self, s32 code, s32 flag, const char *name) {
    WmDWork *wm;

    wm = (WmDWork *)self;
    if (code == 6 || (u32)(code - 3) <= 1) {
        Knife_Comm_WirelessManager_internalReset(self);
        return 0;
    }
    if (code == 8) {
        wm->state = 15;
        wm->timer = 0;
        return 0;
    }
    if (code == 1) {
        if (flag != 0) {
            Knife_Comm_WirelessManager_internalReset(self);
        }
        return 0;
    }
    return 1;
}

// WirelessManager::checkCallbackResult (0x020927c0): checks a callback result. Error codes 3, 4 and 6 set the timer to
// -999 and return FALSE; code 8 sets it to -1000 and returns FALSE; any other code returns TRUE and leaves the timer.
extern "C" BOOL Knife_Comm_WirelessManager_checkCallbackResult(void *self, void *result);
ARM BOOL Knife_Comm_WirelessManager_checkCallbackResult(void *self, void *result) {
    WmDWork *wm;
    WmCallbackHead *head;
    u16 code;

    wm = (WmDWork *)self;
    head = (WmCallbackHead *)result;
    code = head->errCode;
    if (code == 6 || (u16)(code + 0xfffd) <= 1) {
        wm->timer = -999;
        return 0;
    }
    if (code == 8) {
        wm->timer = -1000;
        return 0;
    }
    return 1;
}
