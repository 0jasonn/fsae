#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/cardbus_lock_api.h"
#include "sdk/os/os_wrap_api.h"

// Lock word helpers. LockWord_TryLock forwards to OSi_DoTryLockByWord with FIQ left enabled. CardBus_Acquire and
// CardBus_Release take the card bus lock word at 0x02ffffe0 through the lock word helpers (LockWord_TryLock and
// Os_DoUnlockByWordWrap in the dsd names), passing OSi_AllocateCardBus or OSi_FreeCardBus as the control function.

s32 LockWord_TryLock(u16 lockId, OsLockWord *lock, void (*control)(void)) {
    return OSi_DoTryLockByWord(lockId, lock, control, 0);
}

s32 CardBus_Release(u16 lockId) {
    return Os_DoUnlockByWordWrap(lockId, (OsLockWord *)0x2ffffe0, OSi_FreeCardBus);
}

s32 CardBus_Acquire(u16 lockId) {
    return LockWord_TryLock(lockId, (OsLockWord *)0x2ffffe0, OSi_AllocateCardBus);
}
