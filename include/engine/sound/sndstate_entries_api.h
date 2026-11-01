#ifndef ENGINE_SNDSTATE_ENTRIES_API_H
#define ENGINE_SNDSTATE_ENTRIES_API_H

// Functions defined in src/engine/sndstate_entries*.cpp.

#include "engine/entity.h"

extern "C" {
s32 SndState_RunEntries(u32 id, u32 a1);
}

#endif
