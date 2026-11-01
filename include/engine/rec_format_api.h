#ifndef ENGINE_REC_FORMAT_API_H
#define ENGINE_REC_FORMAT_API_H

// Functions defined in src/engine/rec_format*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL Rec_formatCond(void *self, u32 value, u16 half, s32 arg);
s32 Rec_formatHalfOrU32(void *self, u32 value, s32 arg);
s32 Rec_formatU32(void *self, u32 value, s32 arg);
}

#endif
