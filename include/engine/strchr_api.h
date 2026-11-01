#ifndef ENGINE_STRCHR_API_H
#define ENGINE_STRCHR_API_H

// Functions defined in src/engine/strchr*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *Str_FindChar(const u8 *str, s32 value);
}

#endif
