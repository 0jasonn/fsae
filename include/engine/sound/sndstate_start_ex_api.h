#ifndef ENGINE_SNDSTATE_START_EX_API_H
#define ENGINE_SNDSTATE_START_EX_API_H

// Functions defined in src/engine/sndstate_start_ex*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL SndState_StartEntryEx(u8 *self, s32 a1, s32 a2, s32 a3, void *arg4, s32 arg5);
}

#endif
