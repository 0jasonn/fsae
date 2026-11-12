#ifndef KNIFE_APP_KNIFE_HUD_SETACTIVEPLAYER_H
#define KNIFE_APP_KNIFE_HUD_SETACTIVEPLAYER_H

#include "engine/functions.h"
#include "knife/app/knife_hud.h"
#include "knife/app/knife_hud_layout.h"

// Equip icon positions of the two interpolations (rodata, two VecFx32 each)
typedef struct EquipIconPositions {
    VecFx32 pos[2];
} EquipIconPositions;
extern const EquipIconPositions data_020ddd5c; // positions while no player is active
extern const EquipIconPositions data_020ddd74; // positions while a player is active

namespace Knife {
VecFx32 Interp_VecFx32_Linear(const VecFx32 &a, const VecFx32 &b, s32 t); // 0x0209fb58
}

// Knife::Hud::HudManager::interp_EquipIcon (0x0209fa70, C++ linkage with pointer parameters)
VecFx32 Knife_Hud_HudManager_interp_EquipIcon(const VecFx32 *from, const VecFx32 *to, s32 t);

extern "C" {
void Knife_Hud_HudManager_transferUnactiveEquipIconBasePalette(Knife::Hud::HudManager *self, int player);
}

#endif
