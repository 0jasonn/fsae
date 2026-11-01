#ifndef ENGINE_KNIFE_SOUND_API_H
#define ENGINE_KNIFE_SOUND_API_H

// Functions defined in src/engine/knife_sound*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Sound_StaticObject_clear(u32 *self);
void Knife_Sound_StaticObject_dtor(void *self);
void Knife_Sound_System_destroyWaveHandles(void);
void *Knife_Sound_WaveHandle_WaveHandle(void *self);
}

#endif
