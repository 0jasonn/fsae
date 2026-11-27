#ifndef ENGINE_SOUND_SNDSYS_API_H
#define ENGINE_SOUND_SNDSYS_API_H

// Functions defined in src/engine/sndsys*.cpp.

#include "engine/entity.h"

extern "C" {
s32 SndSys_CheckValue(void *obj, s32 value);
s32 SndSys_StartSlot(s32 slotIndex, void *record, u32 size);
BOOL func_020c1660(void *record);
void SndSys_StopActiveTimer(void);
void SndSys_StopAll(void);
}

#endif
