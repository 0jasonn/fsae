#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_standard.h"
#include "sdk/wm/wm_system.h"

// WM_EndScan(callback) (0x0201fd2c): stops scanning (WM_EndScan command 0xb) once WM is in the scan state.
s32 WM_EndScan(void *callback) {
    s32 result = WMi_CheckStateEx(1, 5);

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(0xb, (WmCallback)callback);
    result = WMi_SendCommand(0xb, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}
