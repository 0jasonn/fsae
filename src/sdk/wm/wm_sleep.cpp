#include "sdk/wm/wm_api.h"

extern u32 data_0212b968;

// Provisional name. Remove the callback record used by WMi_RegisterSleepCallback.
void WMi_UnregisterSleepCallback(void) {
    PmList_DeleteFirst(&data_0212b968);
}

// Provisional name. The registered callback terminates the program.
void OSi_TerminateThunk(void) {
    OS_Terminate();
}
