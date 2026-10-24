#ifndef WIP_B_CHANGE_BUFFER_H
#define WIP_B_CHANGE_BUFFER_H

#include "engine/entity.h"

// Calls that engine/functions.h does not declare yet (reviewer: move them to functions.h).
u8 Knife_GetManualFlag(void);                // arm, 0x02082f94 (knifeExitCallback), no original name
void func_0218a860(s32 arg);             // target outside the ARM9 image (module none in relocs.txt), no original name
extern "C" int Knife_Comm_WirelessManager_getAID(void *manager); // original Knife::Comm::WirelessManager::getAID() const
extern "C" int Knife_Comm_GetPlayerNoByAID(int aid, const void *groupInfo); // original Knife::Comm::GetPlayerNoByAID

#endif
