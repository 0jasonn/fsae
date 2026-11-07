#include "engine/functions.h"
#include "global.h"
#include "engine/fxmul.h"
#include "engine/knife_interp_decel.h"

// Functions in this file (original names from the debug build):
//   Knife::Interp_Fx32_Decel (0x0209fb00)

namespace Knife {

// Interp_Fx32_Decel(long const&, long const&, long) (0x0209fb00): two rounded steps of (a - b) * (t - 1.0) added to b
s32 Interp_Fx32_Decel(const s32 &a, const s32 &b, s32 t) {
    s32 step = FX_Mul(a - b, t - 0x1000);
    return b + FX_Mul(step, t - 0x1000);
}

}
