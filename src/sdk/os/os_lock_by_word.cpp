#include "engine/functions.h"
#include "sdk/os/os_lock.h"
#include "sdk/os/os_interrupts.h"

// Takes a lock word, waiting until it is free.
s32 OSi_DoLockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq) {
    s32 lastFlag = OSi_DoTryLockByWord(lockId, lock, control, disableFiq);
    if (lastFlag > 0) {
        do {
            WaitByLoop(0x400);
            lastFlag = OSi_DoTryLockByWord(lockId, lock, control, disableFiq);
        } while (lastFlag > 0);
    }
    return lastFlag;
}
