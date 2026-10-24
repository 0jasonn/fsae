#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/knife_hud.h"
#include "game/knife_hud_layout.h"

// Functions in this file (original names from the debug build):
//   HudManager::getPlayerPos(int, VecFx32 *) const (0x0209ece8)

// The start*Anim functions (0x0209e794, 0x0209e8cc, 0x0209ea04) are parked in scratch/agentE/nonmatching.

extern s16 *data_02158fa0; // scroll position: x at [1], y at [2]
s8 subtask_getFlag(u32 index); // C++ symbol _Z15subtask_getFlagm

// HudManager::getPlayerPos(int, VecFx32 *) const (0x0209ece8): position of the player's entity in pixels of the
// scroll, 20.12 fixed point
extern "C" void Knife_Hud_HudManager_getPlayerPos(const Knife::Hud::HudManager *self, int player, VecFx32 *pos);
ARM void Knife_Hud_HudManager_getPlayerPos(const Knife::Hud::HudManager *self, int player, VecFx32 *pos) {
    PlayerData *pl = &data_0212ceb0[player];
    s16 scrollX = data_02158fa0[1];
    s16 scrollY = data_02158fa0[2];

    pos->x = (pl->entity->x.HALF.HI - scrollX) << 12;
    pos->y = (pl->entity->y.HALF.HI + pl->entity->z.HALF.HI - scrollY) << 12;
    pos->z = 0;
}
