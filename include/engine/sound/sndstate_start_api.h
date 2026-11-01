#ifndef ENGINE_SNDSTATE_START_API_H
#define ENGINE_SNDSTATE_START_API_H

// Functions defined in src/engine/sndstate_start*.cpp.

#include "engine/entity.h"

extern "C" {
s32 SndState_StartEntry(void *obj, s32 index);
}

#endif
