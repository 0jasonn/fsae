#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/wirelessmgr_d.h"

// Knife::Comm::WirelessManager::getFrameFlag (0x020921b0). getAID (0x020921bc) is parked in scratch/agentD/nonmatching.

// WirelessManager::getFrameFlag (0x020921b0, no original name): the byte at 0x1cdd that update clears each frame.
extern "C" u8 Knife_Comm_WirelessManager_getFrameFlag(void *self);
ARM u8 Knife_Comm_WirelessManager_getFrameFlag(void *self) {
    return WM_FIELD(self, 0x1cdd, u8);
}
