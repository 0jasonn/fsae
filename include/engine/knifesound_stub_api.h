#ifndef ENGINE_KNIFESOUND_STUB_API_H
#define ENGINE_KNIFESOUND_STUB_API_H

// Functions defined in src/engine/knifesound_stub*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Sound_Archive_apply(void *self);
void knifeSoundClearWord(void *self);
void knifeSoundNop2(void *self);
int knifeSoundReturnZero(void *self);
}

#endif
