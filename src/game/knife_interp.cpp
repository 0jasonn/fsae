#include "engine/functions.h"
#include "global.h"
#include "game/knife_interp.h"

// Functions in this file (original names from the debug build):
//   Knife::Interp_VecFx32_None (0x0209fb40)

namespace Knife {

// Interp_VecFx32_None(VecFx32 const&, VecFx32 const&, long) (0x0209fb40): no interpolation, switches from a to b at t = 1.0
ARM VecFx32 Interp_VecFx32_None(const VecFx32 &a, const VecFx32 &b, s32 t) {
    if (t >= 0x1000) {
        return b;
    }
    return a;
}

}
