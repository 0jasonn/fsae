#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Knife::Comm::WirelessManager::getMaxParents-style constant (0x02091d38), in the query range 0x02091cd8 to 0x02091d84.

// WirelessManager::getMaxParents() (0x02091d38, no original name): the number of parent entries (16).
extern "C" s32 Knife_Comm_WirelessManager_getMaxParents(void *self);
ARM s32 Knife_Comm_WirelessManager_getMaxParents(void *self) {
    return 0x10;
}

