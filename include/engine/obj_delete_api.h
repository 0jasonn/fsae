#ifndef ENGINE_OBJ_DELETE_API_H
#define ENGINE_OBJ_DELETE_API_H

// Functions defined in src/engine/obj_delete*.cpp.

#include "engine/entity.h"

extern "C" {
void *Obj_DeleteAfterStub(void *self);
void *Obj_DeletePassthrough(void *self);
}

#endif
