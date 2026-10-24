#include "engine/functions.h"
#include "global.h"
#include "game/knife_power.h"

// Functions in this file (original names from the debug build):
//   Knife::PowerManager::initialize (0x020c8158), Knife::PowerManager::finalize (0x020c8170),
//   Knife::PowerManager::isActive (0x020c8198, provisional name)

namespace Knife {

// Knife::PowerManager::initialize() (0x020c8158): finalizes the state, then marks the manager active
ARM void PowerManager::initialize(void) {
    finalize();
    active = 1;
}

// Knife::PowerManager::finalize() (0x020c8170): clears the state
ARM void PowerManager::finalize(void) {
    active = 0;
    sleepLockCount = 0;
    unk_0c = 1;
    unk_0d[0] = 0;
    unk_0d[1] = 0;
    unk_0d[2] = 0;
    unk_0d[3] = 0;
}

// Provisional name for Knife_PowerManager_isActive: returns the active flag
ARM s32 PowerManager::isActive(void) {
    return active;
}

}
