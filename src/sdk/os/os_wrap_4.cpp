#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/os_wrap_api.h"

// Calls OSi_DoUnlockByWord with FIQ left enabled.
s32 Os_DoUnlockByWordWrap(u16 lockId, OsLockWord *lock, void (*control)(void)) {
    return OSi_DoUnlockByWord(lockId, lock, control, 0);
}
