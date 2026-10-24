#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (original names from the debug build, or guessed where marked):
//   HudManager::startCallAnim (0x0209eb3c), isJustStartedCallAnim (0x0209eb58), setStateOne (0x0209eb70, name guessed)

namespace Knife {
namespace Hud {

// HudManager::startCallAnim(int) (0x0209eb3c): a call animation that is pending (negative) starts and is cleared
ARM BOOL HudManager::startCallAnim(int player) {
    if (callAnim[player] < 0) {
        callAnim[player] = 0;
        return TRUE;
    }
    return FALSE;
}

// HudManager::isJustStartedCallAnim(int) const (0x0209eb58): true while the call animation has just started
ARM BOOL HudManager::isJustStartedCallAnim(int player) const {
    return callAnim[player] == 1;
}

// HudManager::setStateOne (0x0209eb70, name guessed): sets the game-over state to 1
ARM void HudManager::setStateOne(void) {
    state170 = 1;
}

}
}
