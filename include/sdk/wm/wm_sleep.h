#ifndef SDK_WM_WM_SLEEP_H
#define SDK_WM_WM_SLEEP_H

#include "engine/entity.h"

extern "C" {
void WMi_UnregisterSleepCallback(void);
void OSi_TerminateThunk(void);
}

#endif
