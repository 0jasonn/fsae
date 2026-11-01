#ifndef ENGINE_OBJ_ENTRY_API_H
#define ENGINE_OBJ_ENTRY_API_H

// Functions defined in src/engine/obj_entry*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *ObjEntry_Get(u32 index);
void ObjEntry_Setup(u32 index, u32 a, u32 b);
}

#endif
