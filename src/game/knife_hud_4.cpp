#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (names guessed from the stored state, the debug build has none, except isGameoverMode):
//   HudManager::setStateThree (0x0209ecbc), setStateNone (0x0209ecc8), isGameoverMode (0x0209ecd4)

namespace Knife {
namespace Hud {

// HudManager::setStateThree (0x0209ecbc, name guessed): sets the game-over state to 3
ARM void HudManager::setStateThree(void) {
    state170 = 3;
}

// HudManager::setStateNone (0x0209ecc8, name guessed): clears the game-over state
ARM void HudManager::setStateNone(void) {
    state170 = 0;
}

// HudManager::isGameoverMode() const (0x0209ecd4): true while the game-over state is set
ARM BOOL HudManager::isGameoverMode(void) const {
    return state170 != 0;
}

}
}
