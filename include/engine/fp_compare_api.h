#ifndef ENGINE_FP_COMPARE_API_H
#define ENGINE_FP_COMPARE_API_H

// Functions defined in src/engine/fp_compare*.cpp.

#include "engine/entity.h"

extern "C" {
s32 Fp_DoubleEqual(u64 a, u64 b);
s32 Fp_DoubleLess(u64 a, u64 b);
s32 Fp_DoubleNotEqual(u64 a, u64 b);
}

#endif
