#ifndef ENGINE_WSTR_API_H
#define ENGINE_WSTR_API_H

// Functions defined in src/engine/wstr*.cpp.

#include "engine/entity.h"

extern "C" {
u16 *Wstr_FindChar(const u16 *str, s32 value);
}

#endif
