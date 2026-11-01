#ifndef ENGINE_PACKED_RESET_API_H
#define ENGINE_PACKED_RESET_API_H

// Functions defined in src/engine/packed_reset*.cpp.

#include "engine/entity.h"

extern "C" {
void *Packed_deletingDtor(void *self);
void *Packed_resetSelf(void *self);
}

#endif
