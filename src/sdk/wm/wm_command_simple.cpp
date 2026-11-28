#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/wm/wm_system.h"
#include "sdk/wm/wm_sleep.h"
#include "sdk/wm/wm_standard.h"

// WMi_EnableEx(callback, flag) (0x0201f848): starts the WM_Enable command (3) with the work area description (first,
// second and fifth word of the work area) and the extra flag.
s32 WMi_EnableEx(void *callback, u32 flag) {
    s32 result;
    WmWork *work;

    result = WMi_CheckStateEx(1, 0);
    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(3, (WmCallback)callback);
    WMi_RegisterSleepCallback();
    work = (WmWork *)WMi_GetWorkPointer();
    result = WMi_SendCommand(3, 4, work->arm7Buf, work->status, work->fifo7to9, flag);
    if (result == 0) {
        result = 2;
    }
    return result;
}

// WM_Disable(callback) (0x0201f8b4): starts the WM_Disable command (4) once WM is in the stop state.
u32 WM_Disable(void *callback) {
    s32 result = WMi_CheckStateEx(1, 1);

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(4, (WmCallback)callback);
    result = WMi_SendCommand(4, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}

// WM_PowerOn(callback) (0x0201f8f8): starts the WM_PowerOn command (5) once WM is in the stop state.
u32 WM_PowerOn(void *callback) {
    s32 result = WMi_CheckStateEx(1, 1);

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(5, (WmCallback)callback);
    result = WMi_SendCommand(5, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}

// WM_PowerOff(callback) (0x0201f93c): starts the WM_PowerOff command (6) once WM is in the idle state.
s32 WM_PowerOff(void *callback) {
    s32 result = WMi_CheckStateEx(1, 2);

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(6, (WmCallback)callback);
    result = WMi_SendCommand(6, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}

// WM_Reset(callback) (0x0201f984): starts the WM_Reset command (1) in any state above idle.
s32 WM_Reset(void *callback) {
    s32 result = WMi_CheckIdle();

    if (result != 0) {
        return result;
    }
    WMi_SetCallbackTable(1, (WmCallback)callback);
    result = WMi_SendCommand(1, 0);
    if (result == 0) {
        result = 2;
    }
    return result;
}
