#ifndef ENGINE_SNDCHANNEL_API_H
#define ENGINE_SNDCHANNEL_API_H

// Functions defined in src/engine/sndchannel*.cpp.

#include "engine/entity.h"

extern "C" {
s32 SndChannel_TryLock(u32 mask);
}

#endif
