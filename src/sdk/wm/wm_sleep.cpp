#include "sdk/wm/wm_sleep.h"
#include "sdk/pm/pm.h"
#include "sdk/wm/wm_system.h"
#include "engine/functions.h"

// Provisional name. Remove the callback record used by WMi_RegisterSleepCallback.
void WMi_UnregisterSleepCallback(void) {
    PmList_DeleteFirst(&data_0212b960.sleepCallback);
}

// Provisional name. The registered callback terminates the program.
void OSi_TerminateThunk(void) {
    OS_Terminate();
}
