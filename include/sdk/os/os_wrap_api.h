#ifndef SDK_OS_OS_WRAP_API_H
#define SDK_OS_OS_WRAP_API_H

// Functions defined in src/engine/os_wrap*.cpp.

#include "engine/entity.h"
#include "sdk/os/os_lock.h"

extern "C" {
// OSi_DoLockByWord / OSi_DoUnlockByWord with FIQ left enabled (TwlSDK OS_LockByWord, OS_UnlockByWord).
s32 Os_DoLockByWordWrap(u16 lockId, OsLockWord *lock, void (*control)(void));
s32 Os_DoUnlockByWordWrap(u16 lockId, OsLockWord *lock, void (*control)(void));
u32 Os_InitCommonWrap(u32 a, u32 b, u32 c, u32 d);
void OSi_IrqDma0(void);
}

#endif
