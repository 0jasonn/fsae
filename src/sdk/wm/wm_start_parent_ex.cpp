#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_system.h"
#include "sdk/wm/wm_standard.h"

// WMi_StartParentEx(callback, flag) (0x0201fafc): clears the AID and connected-AID state and starts the parent
// (WM_StartParent command 8).
s32 WMi_StartParentEx(void *callback, u32 flag) {
    s32 result = WMi_CheckStateEx(1, 2);
    WmWork *work;

    if (result != 0) {
        return result;
    }
    if (WMi_CheckEnableFlag() == 0) {
        return 4;
    }
    work = (WmWork *)WMi_GetWorkPointer();
    work->aid = 0;
    work->connectedAids = 0;
    WMi_SetCallbackTable(8, (WmCallback)callback);
    result = WMi_SendCommand(8, 1, flag);
    if (result == 0) {
        result = 2;
    }
    return result;
}
