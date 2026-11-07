#ifndef WIP_K_KNIFE_INTERP_DECEL_H
#define WIP_K_KNIFE_INTERP_DECEL_H

#include "types.h"

namespace Knife {

// Interp_Fx32_Decel (0x0209fb00): ease-out of a single 20.12 value from a towards b
s32 Interp_Fx32_Decel(const s32 &a, const s32 &b, s32 t);

}

#endif
