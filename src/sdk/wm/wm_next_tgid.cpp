#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/rtc/rtc.h"
#include "sdk/wm/wm_system.h"

// WM_GetNextTgid() (0x0201f7c8): returns a fresh TGID. The first call seeds the counter from the RTC time (day-of-week
// style words 1 and 2 of the time block), later calls just increment it.
u16 WM_GetNextTgid(void) {
    u32 time[3];

    if (data_020f24c0 == 0x10000) {
        RTC_Init();
        if (RTCi_SetRegAdjust(time) == 0) {
            data_020f24c0 = (u16)(time[2] + (time[1] << 8));
        }
    }
    data_020f24c0 = (u16)(data_020f24c0 + 1);
    return data_020f24c0;
}
