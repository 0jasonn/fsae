#ifndef ENGINE_SNDBANK_API_H
#define ENGINE_SNDBANK_API_H

// Functions defined in src/engine/sndbank*.cpp.

#include "engine/entity.h"

extern "C" {
void SndBank_Detach(void *obj, void *data, s32 index);
void SndBank_ReleaseWaveArc(void *obj, s32 unused, void *data, s32 index);
}

#endif
