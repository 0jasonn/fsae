#ifndef ENGINE_TCLI_ACCESSOR_API_H
#define ENGINE_TCLI_ACCESSOR_API_H

// Functions defined in src/engine/tcli_accessor*.cpp.

#include "engine/entity.h"

extern "C" {
void TCLi_InitAccessor(void *self, u32 a, u32 b, u32 c, u32 d);
}

#endif
