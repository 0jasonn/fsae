#include "sdk/os/os_lock.h"
#include "sdk/os/os_interrupts.h"

// Releases a lock word held by lockId; -2 when another owner holds it.
s32 OSi_DoUnlockByWord(u16 lockId, OsLockWord *lock, void (*control)(void), u32 disableFiq) {
    u32 irq;

    if (lockId != lock->ownerId) {
        return -2;
    }
    if (disableFiq) {
        irq = OS_DisableInterrupts_IrqAndFiq();
    } else {
        irq = OS_DisableInterrupts();
    }
    lock->ownerId = 0;
    if (control) {
        control();
    }
    lock->lockFlag = 0;
    if (disableFiq) {
        OS_RestoreInterrupts_IrqAndFiq(irq);
    } else {
        OS_RestoreInterrupts(irq);
    }
    return 0;
}
