#ifndef ENGINE_PAIR_SETUP_API_H
#define ENGINE_PAIR_SETUP_API_H

// Functions defined in src/engine/pair_setup*.cpp.

#include "engine/entity.h"

extern "C" {
void Pair_Setup(void *buf, s32 n);
}

#endif
