#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/callees.h"

// Lock word helpers. LockWord_TryLock forwards to OSi_DoTryLockByWord with a zero fourth argument. CardBus_Acquire
// and CardBus_Release take the card bus lock word at 0x02ffffe0 through the lock word helpers (LockWord_TryLock and
// func_020172bc in the dsd names), passing OSi_AllocateCardBus or OSi_FreeCardBus as the owner.
extern "C" u32 LockWord_TryLock(void *word, u32 id, void *owner);
extern "C" u32 func_020172bc(void *word, u32 id, void *owner);

extern "C" u32 LockWord_TryLock(void *word, u32 id, void *owner);
extern "C" void CardBus_Release(u32 id);
extern "C" void CardBus_Acquire(u32 id);

ARM u32 LockWord_TryLock(void *word, u32 id, void *owner) {
    return OSi_DoTryLockByWord(word, id, owner, 0);
}

ARM void CardBus_Release(u32 id) {
    func_020172bc((void *)id, 0x2ffffe0, (void *)OSi_FreeCardBus);
}

ARM void CardBus_Acquire(u32 id) {
    LockWord_TryLock((void *)id, 0x2ffffe0, (void *)OSi_AllocateCardBus);
}
