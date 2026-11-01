#ifndef ENGINE_SNDBANK_WAVE_API_H
#define ENGINE_SNDBANK_WAVE_API_H

// Functions defined in src/engine/sndbank_wave*.cpp.

#include "engine/entity.h"

extern "C" {
void SndBank_ReleaseWaveData(void *obj, u32 size, void *table, s32 index);
}

#endif
