#include "sdk/os/os_lock.h"
#include "sdk/mi/frame_asm.h"
#include "sdk/os/os_interrupts.h"

// Tries to take a lock word with swp and returns the previous lock flag.
s32 OSi_DoTryLockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq) {
    u32 irq;
    s32 lastFlag;

    if (disableFiq) {
        irq = OS_DisableInterrupts_IrqAndFiq();
    } else {
        irq = OS_DisableInterrupts();
    }
    lastFlag = Swp_Exchange(lockId, &lock->lockFlag);
    if (lastFlag == 0) {
        if (control) {
            control();
        }
        lock->ownerId = lockId;
    }
    if (disableFiq) {
        OS_RestoreInterrupts_IrqAndFiq(irq);
    } else {
        OS_RestoreInterrupts(irq);
    }
    return lastFlag;
}
