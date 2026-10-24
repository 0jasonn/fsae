#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (name guessed, the debug build has none):
//   HudManager::setField70 (0x0209e788)

namespace Knife {
namespace Hud {

// HudManager::setField70 (0x0209e788): stores a value for a player in the array at +0x70
ARM void HudManager::setField70(int player, int value) {
    field70[player] = value;
}

}
}
