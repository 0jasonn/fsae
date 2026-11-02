#ifndef WIP_F_KNIFECOMM_2_H
#define WIP_F_KNIFECOMM_2_H

// Declarations for the Knife comm group helpers of implementer F (round 16). Callees that are not in engine/functions.h
// are declared here; the reviewer moves the shared ones.

#include "engine/functions.h"
#include "types.h"

extern "C" {
s32 Knife_Comm_GetPlayerNoByAID(s32 aid, const void *groupInfo);
s32 Knife_Comm_GetAIDByPlayerNo(s32 playerNo, const void *groupInfo);
s32 Knife_Comm_GetAIDConvMap(s32 count, const s32 *aids);
u32 MATH_CountPopulation(u32 bits);
void Knife_Comm_removePlayerFromGroup(s32 playerNo, u32 *groupWord);
}

#endif
