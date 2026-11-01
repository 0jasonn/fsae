#ifndef ENGINE_SLOTS_API_H
#define ENGINE_SLOTS_API_H

// Functions defined in src/engine/slots*.cpp.

#include "engine/entity.h"

extern "C" {
void Slots_Set(s32 *slots, u32 index, u32 value);
void Slots_SetAt8(u8 *self, u32 index, u32 value);
}

#endif
