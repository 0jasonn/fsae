#include "engine/functions.h"
#include "global.h"
#include "knife/app/knife_interp.h"
#include "engine/fxmul.h"
#include "engine/knife_interp_decel.h"

// Functions in this file (plain names from the debug build):
//   Knife_Hud_HudManager_interp_EquipIcon (0x0209fa70)

// Knife::Hud::HudManager::interp_EquipIcon(VecFx32 const&, VecFx32 const&, long) (0x0209fa70): x moves linearly from
// the start to the end, y follows the decelerating curve with a target 0x4000 below the start, z is 0
VecFx32 Knife_Hud_HudManager_interp_EquipIcon(const VecFx32 *from, const VecFx32 *to, s32 t) {
    VecFx32 result;
    s32 target = from->y - 0x4000;

    result.y = Knife::Interp_Fx32_Decel(from->y, target, t * 2);
    result.x = from->x + FX_Mul(to->x - from->x, t);
    result.z = 0;
    return result;
}
