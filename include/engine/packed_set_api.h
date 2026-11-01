#ifndef ENGINE_PACKED_SET_API_H
#define ENGINE_PACKED_SET_API_H

// Functions defined in src/engine/packed_set*.cpp.

#include "engine/entity.h"

extern "C" {
void Obj_initVtableB(void *self);
void Packed_noop(void *self);
void Packed_setS16(void *self, s32 value);
void Packed_setU32BE(void *self, u32 value);
}

#endif
