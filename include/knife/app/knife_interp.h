#ifndef KNIFE_APP_KNIFE_INTERP_H
#define KNIFE_APP_KNIFE_INTERP_H

#include "types.h"
#include "sdk/fx/fx.h"

namespace Knife {

// Interp_VecFx32_None (0x0209fb40): returns b once t reaches 1.0 (0x1000), a before that
VecFx32 Interp_VecFx32_None(const VecFx32 &a, const VecFx32 &b, s32 t);

}

#endif
