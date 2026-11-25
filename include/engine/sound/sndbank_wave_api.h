#ifndef ENGINE_SOUND_SNDBANK_WAVE_API_H
#define ENGINE_SOUND_SNDBANK_WAVE_API_H

// Functions defined in src/engine/sndbank_wave*.cpp.

#include "engine/entity.h"

extern "C" {
void SndBank_ReleaseWaveData(void *obj, u32 size, void *table, s32 index);
BOOL func_020c14d8(void *table, s32 index, s32 fileIndex, void *record);
BOOL func_020c15a0(void *table, void *bank, u32 archiveIndex, s32 fileIndex, void *record);
}

#endif
