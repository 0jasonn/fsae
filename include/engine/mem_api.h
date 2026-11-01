#ifndef ENGINE_MEM_API_H
#define ENGINE_MEM_API_H

// Functions defined in src/engine/mem*.cpp.

#include "engine/entity.h"

extern "C" {
void Mem_SetCore(void *dst, s32 value, u32 size);
}

#endif
