#ifndef SDK_OS_OS_LOCK_H
#define SDK_OS_OS_LOCK_H

// TwlSDK OS lock words shared with the other processor (card bus, PXI, VRAM ...).
#include "types.h"

// Lock word: lockFlag is taken with swp (Swp_Exchange) and holds the owner's lock ID while locked, ownerId records the
// holder for the unlock check.
typedef struct OsLockWord {
    /* 00 */ u32 lockFlag;
    /* 04 */ u16 ownerId;
    /* 06 */ u16 extension;
} OsLockWord;

extern "C" {
// control runs while the lock is taken / before it is released; disableFiq also masks FIQ around the access.
// They return 0 on success, the holder's lock ID (> 0) when it is taken, -2 when unlocking a lock held by another ID.
s32 OSi_DoLockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq);
s32 OSi_DoUnlockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq);
s32 OSi_DoTryLockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq);
// Not decompiled yet.
s32 OS_GetLockID(void);
void OS_ReleaseLockID(u16 lockId);
}

#endif
