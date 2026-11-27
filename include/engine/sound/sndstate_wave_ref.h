#ifndef ENGINE_SOUND_SNDSTATE_WAVE_REF_H
#define ENGINE_SOUND_SNDSTATE_WAVE_REF_H

#include "types.h"

typedef struct SndStateAcquireDescriptor {
    u32 index : 24;
    u32 kind : 8;
} SndStateAcquireDescriptor;

#endif
