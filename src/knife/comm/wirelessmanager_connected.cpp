#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/wm_d.h"
#include "knife/comm/wm_irq.h"
#include "knife/comm/wirelessmanager_connected_api.h"

// Knife::Comm::WirelessManager connected-AID and link level queries, 0x02092234 to 0x020922ec.

extern "C" u16 WM_GetConnectedAIDs(void);
extern "C" u16 WM_GetLinkLevel(void);
extern "C" s32 MATH_CountPopulation(u32 value);

// Parked in scratch/agentD/nonmatching/Knife_Comm_WirelessManager_getConnectedAIDs.cpp (not part of this unit).
extern "C" u16 Knife_Comm_WirelessManager_getConnectedAIDs(void *self);

// WirelessManager::getLinkLevel() const (0x020922d0): the number of set bits in the connected AIDs.
extern "C" s32 Knife_Comm_WirelessManager_getLinkLevel(void *self);
s32 Knife_Comm_WirelessManager_getLinkLevel(void *self) {
    return MATH_CountPopulation(Knife_Comm_WirelessManager_getConnectedAIDs(self));
}

// WM_GetLinkLevel wrapper (0x020922e0, invented name): a tail call to the SDK function.
u16 Knife_Comm_WirelessManager_sdkGetLinkLevel(void) {
    return WM_GetLinkLevel();
}
