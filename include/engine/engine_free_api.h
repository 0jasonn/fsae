#ifndef ENGINE_ENGINE_FREE_API_H
#define ENGINE_ENGINE_FREE_API_H

// Functions defined in src/engine/engine_free*.cpp.

#include "engine/entity.h"

extern "C" {
void FreeToSystemHeap(void *block);
}

#endif
