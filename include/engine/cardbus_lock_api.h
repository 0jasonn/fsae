#ifndef ENGINE_CARDBUS_LOCK_API_H
#define ENGINE_CARDBUS_LOCK_API_H

// Functions defined in src/engine/cardbus_lock*.cpp.

#include "engine/entity.h"

extern "C" {
void CardBus_Acquire(u32 id);
void CardBus_Release(u32 id);
u32 LockWord_TryLock(void *word, u32 id, void *owner);
}

#endif
