#ifndef ENGINE_HALFWORD_API_H
#define ENGINE_HALFWORD_API_H

// Functions defined in src/engine/halfword*.cpp.

#include "engine/entity.h"

extern "C" {
u16 *Mem_FindHalfword(const u16 *buf, s32 value, u32 count);
}

#endif
