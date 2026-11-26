#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/dc_cache.h"
#include "sdk/wm/wm_system.h"

// WMi_CheckInitialized() (0x0201edec): 0 when WM_Init has run, 3 (uninitialised) otherwise.
s32 WMi_CheckInitialized(void) {
    if (data_0212b960.initialized != 0) {
        return 0;
    }
    return 3;
}

// WMi_CheckIdle() (0x0201ee08): 0 when the WM state is above idle, 3 (illegal state) otherwise.
s32 WMi_CheckIdle(void) {
    s32 result = WMi_CheckInitialized();

    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(data_0212b960.work->status, 2);
    if (data_0212b960.work->status->state <= 1) {
        return 3;
    }
    return 0;
}

// WMi_CheckStateEx(count, state...) (0x0201ee4c): 0 when the current WM state is one of the listed states, else 3. The
// variadic words are read straight from the caller's stack (there is no stdarg header).
s32 WMi_CheckStateEx(s32 count, ...) {
    s32 result = WMi_CheckInitialized();
    u8 *args;
    u16 state;

    if (result != 0) {
        return result;
    }
    DC_InvalidateRange(data_0212b960.work->status, 2);
    state = data_0212b960.work->status->state;
    args = (u8 *)((((u32)&count) & ~3) + 4);
    result = 3;
    while (count != 0) {
        if (*(u32 *)((args += 4) - 4) == state) {
            result = 0;
        }
        count--;
    }
    return result;
}
