#include "engine/functions.h"
#include "global.h"
#include "game/knife_hud.h"

// Functions in this file (original names from the debug build):
//   HudManager::initialize (0x0209e0ac)

namespace Knife {
namespace Hud {

// HudManager::initialize() (0x0209e0ac): resets the manager and marks it initialized
ARM void HudManager::initialize(void) {
    finalize();
    initialized = 1;
}

}
}
