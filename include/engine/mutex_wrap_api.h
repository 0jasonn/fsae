#ifndef ENGINE_MUTEX_WRAP_API_H
#define ENGINE_MUTEX_WRAP_API_H

// Functions defined in src/engine/mutex_wrap*.cpp.

#include "engine/entity.h"

extern "C" {
void Mutex_LockGlobal(void);
void Mutex_UnlockGlobal(void);
}

#endif
