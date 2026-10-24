#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   Knife::Comm::GetPlayerNoByAID (0x020ae318), Knife::Comm::GetAIDByPlayerNo (0x020ae338),
//   Knife_Comm_setPlayerBit (0x020ae358, provisional name Knife_Comm_setPlayerBit: sets a player bit in the group word),
// Knife::Comm::GetAIDConvMap (0x020ae4a4) is parked in scratch/agentF/nonmatching/Knife_Comm_GetAIDConvMap.cpp

extern "C" {
s32 Knife_Comm_GetPlayerNoByAID(s32 aid, const void *groupInfo);
s32 Knife_Comm_GetAIDByPlayerNo(s32 playerNo, const void *groupInfo);
void Knife_Comm_setPlayerBit(s32 playerNo, u32 *groupWord);
u32 MATH_CountPopulation(u32 bits);
}

// Group word: low nibble = the players of the group as a bit mask, bits 4-6 = the group type
typedef struct KnifeGroupWord {
    u32 playerMask : 4;
    u32 groupType : 3;
    u32 unk : 25;
} KnifeGroupWord;

// Lookup tables in rodata: one row of four values per group type (the type is bits 4-6 of the group word)
extern const s32 data_020deac8[][4];
extern const s32 data_020deb28[][4];

// Knife::Comm::GetPlayerNoByAID (0x020ae318): player number of an AID in the group
ARM s32 Knife_Comm_GetPlayerNoByAID(s32 aid, const void *groupInfo) {
    u32 groupType;

    groupType = ((u32 *)groupInfo)[0] << 25 >> 29;
    return data_020deac8[groupType][aid];
}

// Knife::Comm::GetAIDByPlayerNo (0x020ae338): AID of a player number in the group
ARM s32 Knife_Comm_GetAIDByPlayerNo(s32 playerNo, const void *groupInfo) {
    u32 groupType;

    groupType = ((u32 *)groupInfo)[0] << 25 >> 29;
    return data_020deb28[groupType][playerNo];
}

// Knife_Comm_setPlayerBit (0x020ae358): with playerNo 0 resets the group word to the single player mask 1, type 0;
// otherwise adds playerNo to the player mask
ARM void Knife_Comm_setPlayerBit(s32 playerNo, u32 *groupWord) {
    KnifeGroupWord *g;
    u32 mask;

    g = (KnifeGroupWord *)groupWord;
    if (playerNo == 0) {
        g->playerMask = 1;
        g->groupType = 0;
        return;
    }
    MATH_CountPopulation(g->playerMask);
    mask = (1 << playerNo) | g->playerMask;
    g->playerMask = mask;
}
