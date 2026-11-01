#ifndef ENGINE_M4A_API_H
#define ENGINE_M4A_API_H

// Functions defined in src/engine/m4a*.cpp.

#include "engine/entity.h"

extern "C" {
void m4aSongNumSetPlayerValue(u16 songNum, s32 value);
void m4aSongNumSetVolume(u16 songNum, u16 volume);
u32 m4aSongNumStartOrContinue(u16 songNum);
void m4aSongNumStop(u16 songNum);
void pauseWavePlayer(s32 pause);
}

#endif
