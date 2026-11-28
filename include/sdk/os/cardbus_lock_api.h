#ifndef SDK_OS_CARDBUS_LOCK_API_H
#define SDK_OS_CARDBUS_LOCK_API_H

// Functions defined in src/sdk/os/cardbus_lock*.cpp: the card bus lock word at 0x02ffffe0 (TwlSDK OS_TryLockCard,
// OS_UnlockCard) and OSi_DoTryLockByWord with FIQ left enabled (OS_TryLockByWord).

#include "engine/entity.h"
#include "sdk/os/os_lock.h"

extern "C" {
s32 CardBus_Acquire(u16 lockId);
s32 CardBus_Release(u16 lockId);
void OSi_FreeCardBus(void);
s32 LockWord_TryLock(u16 lockId, OsLockWord *lock, void (*control)(void));
}

#endif
