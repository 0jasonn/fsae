#ifndef ENGINE_WM_API_H
#define ENGINE_WM_API_H

#include "types.h"

extern "C" {
void *WMi_GetWorkPointer(void);
void WMi_UnregisterSleepCallback(void);
void OSi_TerminateThunk(void);
s32 WM_Enable(void *callback);
s32 WM_StartParent(void *callback);
BOOL WMi_ValidateParentParameter(const void *parameter);

void PmList_DeleteFirst(void *item);
void OS_Terminate(void);
s32 WMi_EnableEx(void *callback, u32 flag);
s32 WMi_StartParentEx(void *callback, u32 flag);
}

#endif
