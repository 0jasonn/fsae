#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"
#include "sdk/wm/wm_system.h"
#include "sdk/wm/wm_sleep.h"

// WMi_RegisterSleepCallback() (0x0201f348): registers the WM sleep callback record with the PM post-exit hook list.
void WMi_RegisterSleepCallback(void) {
    data_0212b960.sleepCallback = OSi_TerminateThunk;
    data_0212b960.sleepCallbackArg = 0;
    WBT_MpChildSendHook(&data_0212b960.sleepCallback, 1000);
}
