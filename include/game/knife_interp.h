#ifndef WIP_E_KNIFE_INTERP_H
#define WIP_E_KNIFE_INTERP_H

#include "types.h"

// Fixed point vector (VecFx32 of the NitroSDK): x, y and z in 20.12 format
typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

namespace Knife {

// Interp_VecFx32_None (0x0209fb40): returns b once t reaches 1.0 (0x1000), a before that
VecFx32 Interp_VecFx32_None(const VecFx32 &a, const VecFx32 &b, s32 t);

}

#endif
