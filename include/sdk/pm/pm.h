#ifndef SDK_PM_PM_H
#define SDK_PM_PM_H

// TwlSDK PM library (pm.c): LCD power and the post-exit callback lists.
#include "types.h"

// Heads of the two callback lists PMi_InsertList / PMi_DeleteList work on. The list items are 0x10-byte callback
// records owned by the caller.
extern void *data_0212b924; // appended to by PM_AppendPostExitCallback
extern void *data_0212b93c; // prepended to by PM_PrependPostExitCallback, insertion by priority in WBT_MpChildSendHook

extern "C" {
void PMi_DummyCallback(u32 result, u32 *out);
s32 PM_SetLCDPower(s32 on);
s32 PM_GetLCDPower(void);
void PM_PrependPostExitCallback(void *item);
void PM_AppendPostExitCallback(void *item);
void WBT_MpChildSendHook(void *item, s32 priority);
void PmList_DeleteFirst(void *item);
void PmList_DeleteSecond(void *item);

// Not decompiled yet.
void PMi_InsertList(void **list, void *item, s32 priority, s32 prepend);
void PMi_DeleteList(void **list, void *item);
void PMi_SetDispOffCount(void);
}

#endif
