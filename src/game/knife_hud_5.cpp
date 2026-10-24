#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (original names from the debug build):
//   HudManager::getPlayerDir (0x0209ed4c)

extern PlayerData data_0212ceb0[4];

namespace Knife {
namespace Hud {

// HudManager::getPlayerDir(int) const (0x0209ed4c): half the animation value of the player's entity
ARM int HudManager::getPlayerDir(int player) const {
    PlayerData *pl = &data_0212ceb0[player];

    return pl->entity->animationState >> 1;
}

}
}
