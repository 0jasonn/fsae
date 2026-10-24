#include "engine/functions.h"
#include "global.h"
#include "game/knife_interp.h"

// Functions in this file (original names from the debug build):
//   Knife::Interp_VecFx32_Linear (0x0209fb58), Knife::Interp_VecFx32_Decel (0x0209fbec)

namespace Knife {

// Interp_VecFx32_Linear(VecFx32 const&, VecFx32 const&, long) (0x0209fb58): a + (b - a) * t, per component, t in 1/0x1000
ARM VecFx32 Interp_VecFx32_Linear(const VecFx32 &a, const VecFx32 &b, s32 t) {
    VecFx32 r;
    s32 dx = b.x - a.x;
    s32 dy = b.y - a.y;
    s32 dz = b.z - a.z;

    r.x = a.x + (s32)((((s64)dx * t) + 0x800) >> 12);
    r.y = a.y + (s32)((((s64)dy * t) + 0x800) >> 12);
    r.z = a.z + (s32)((((s64)dz * t) + 0x800) >> 12);
    return r;
}

// Interp_VecFx32_Decel(VecFx32 const&, VecFx32 const&, long) (0x0209fbec): two rounded steps of (a - b) * k with k = t - 1.0,
// added to b, per component (the ease-out curve)
ARM VecFx32 Interp_VecFx32_Decel(const VecFx32 &a, const VecFx32 &b, s32 t) {
    VecFx32 r;
    s32 k = t - 0x1000;
    s32 dx = a.x - b.x;
    s32 dy = a.y - b.y;
    s32 dz = a.z - b.z;
    s32 e;

    e = (s32)((((s64)dx * k) + 0x800) >> 12);
    r.x = b.x + (s32)((((s64)e * k) + 0x800) >> 12);
    e = (s32)((((s64)dy * k) + 0x800) >> 12);
    r.y = b.y + (s32)((((s64)e * k) + 0x800) >> 12);
    e = (s32)((((s64)dz * k) + 0x800) >> 12);
    r.z = b.z + (s32)((((s64)e * k) + 0x800) >> 12);
    return r;
}

}
