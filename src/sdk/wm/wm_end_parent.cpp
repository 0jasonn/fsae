#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_standard.h"
#include "sdk/wm/wm_system.h"

// WM_EndParent(callback) (0x0201fb84): stops the parent (WM_EndParent command 9) once WM is in the parent state.
u32 WM_EndParent(void *callback) {
    s32 result = WMi_CheckStateEx(1, 7);

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(9, (WmCallback)callback);
    result = WMi_SendCommand(9, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}
