#ifndef ENGINE_BITSTREAM_H
#define ENGINE_BITSTREAM_H

#include "engine/entity.h"

extern "C" {
u32 BitStream_ReadBits(u8 *self, s32 bits);
}

#endif
