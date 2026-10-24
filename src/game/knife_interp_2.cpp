#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud_layout.h"

// Functions in this file (original names from the debug build):
//   Knife::Interp<VecFx32>::~Interp() (0x0209faec, deleting destructor)

extern "C" KnifeHudInterp *Knife_Interp_VecFx32__dtor_Interp(KnifeHudInterp *self);

// Knife::Interp<VecFx32>::~Interp() (0x0209faec): deleting destructor, frees the interpolation and returns it
ARM KnifeHudInterp *Knife_Interp_VecFx32__dtor_Interp(KnifeHudInterp *self) {
    operator delete(self);
    return self;
}
