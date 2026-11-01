#ifndef ENGINE_FP_SIGN_API_H
#define ENGINE_FP_SIGN_API_H

// Functions defined in src/engine/fp_sign*.cpp.

#include "engine/entity.h"

extern "C" {
f64 Fp_Abs(f64 x);
f64 Fp_CopySign(f64 x, f64 y);
}

#endif
