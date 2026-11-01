#ifndef ENGINE_SNDSYS_API_H
#define ENGINE_SNDSYS_API_H

// Functions defined in src/engine/sndsys*.cpp.

#include "engine/entity.h"

extern "C" {
s32 SndSys_CheckValue(void *obj, s32 value);
s32 SndSys_StartSlot(s32 slotIndex, void *arg1, void *arg2);
void SndSys_StopActiveTimer(void);
}

#endif
