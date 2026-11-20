#ifndef SDK_SND_MUTEX_WRAP_API_H
#define SDK_SND_MUTEX_WRAP_API_H

// Functions defined in src/engine/mutex_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
void Mutex_LockGlobal(void);
void Mutex_UnlockGlobal(void);
}

#endif
