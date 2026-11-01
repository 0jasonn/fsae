#ifndef ENGINE_BITS_API_H
#define ENGINE_BITS_API_H

// Functions defined in src/engine/bits*.cpp.

#include "engine/entity.h"

extern "C" {
u8 Bits_PopCount64(u64 x);
s32 Fp_SignBit(f64 x);
}

#endif
