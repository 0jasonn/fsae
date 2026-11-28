#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_standard.h"
#include "sdk/wm/wm_system.h"

// WM_Disconnect(callback, aid) (0x0201fe50): disconnects one child (parent state: aid 1-15 that is connected) or the
// parent itself (child state: aid 0); sends WM_Disconnect (command 0xd) with a bit mask of the AID.
u32 WM_Disconnect(void *callback, u16 aid) {
    WmWork *work = (WmWork *)WMi_GetWorkPointer();
    s32 result = WMi_CheckStateEx(5, 7, 9, 8, 10, 11);

    if (result != 0) {
        return result;
    }
    if (work->status->state == 7 || work->status->state == 9) {
        if (aid < 1 || aid > 15) {
            return 6;
        }
        DC_InvalidateRange(&work->status->mpReadyBitmap, 2);
        if (!(work->status->mpReadyBitmap & (1 << aid))) {
            return 7;
        }
    } else if (aid != 0) {
        return 6;
    }
    WMi_SetCallbackTable(0xd, (WmCallback)callback);
    result = WMi_SendCommand(0xd, 1, 1 << aid);
    if (result == 0) {
        result = 2;
    }
    return result;
}
