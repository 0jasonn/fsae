#ifndef ENGINE_SNDSTATE_LOOKUP_API_H
#define ENGINE_SNDSTATE_LOOKUP_API_H

// Functions defined in src/engine/sndstate_lookup*.cpp.

#include "engine/entity.h"

extern "C" {
u8 *SndState_LookupAt10(s32 index);
u8 *SndState_LookupAt14(s32 index);
u8 *SndState_LookupAt18(s32 index);
}

#endif
