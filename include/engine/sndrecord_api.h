#ifndef ENGINE_SNDRECORD_API_H
#define ENGINE_SNDRECORD_API_H

// Functions defined in src/engine/sndrecord*.cpp.

#include "engine/entity.h"

extern "C" {
void SndList_Reset(void *list);
void SndSys_FlushAndWait(void);
}

#endif
