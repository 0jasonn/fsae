#ifndef WIP_C_HUD_H
#define WIP_C_HUD_H

#include "types.h"
#include "knife/app/knife_interp.h"

// VecFx32 initial values for the status-up animations (copied by the start*UpAnim members).
extern const VecFx32 data_020ddd14; // startSpeedUpAnim from
extern const VecFx32 data_020ddd20; // startSpeedUpAnim to
extern const VecFx32 data_020ddd2c; // startPowerUpAnim from
extern const VecFx32 data_020ddd38; // startPowerUpAnim to
extern const VecFx32 data_020ddcfc; // startDefenceUpAnim from
extern const VecFx32 data_020ddd08; // startDefenceUpAnim to

namespace Knife {
VecFx32 Interp_VecFx32_Decel(const VecFx32 &a, const VecFx32 &b, s32 t);
}

#endif
