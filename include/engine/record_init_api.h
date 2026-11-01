#ifndef ENGINE_RECORD_INIT_API_H
#define ENGINE_RECORD_INIT_API_H

// Functions defined in src/engine/record_init*.cpp.

#include "engine/entity.h"

extern "C" {
void Record_Init(u8 *self, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
}

#endif
