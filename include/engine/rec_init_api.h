#ifndef ENGINE_REC_INIT_API_H
#define ENGINE_REC_INIT_API_H

// Functions defined in src/engine/rec_init*.cpp.

#include "engine/entity.h"

extern "C" {
s32 Rec_setName(void *self, const void *name);
}

#endif
