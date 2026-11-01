#ifndef ENGINE_SNDBANK_ACQUIRE_API_H
#define ENGINE_SNDBANK_ACQUIRE_API_H

// Functions defined in src/engine/sndbank_acquire*.cpp.

#include "engine/entity.h"

extern "C" {
void *SndBank_AcquireBank(s32 index, void *record, s32 flag);
void *SndBank_AcquireWave(s32 index, void *record, s32 flag);
}

#endif
