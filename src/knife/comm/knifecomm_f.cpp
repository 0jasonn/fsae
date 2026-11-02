#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "ui/widget/knifecomm_f.h"

// knifecomm_2: function Knife_Comm_removePlayerFromGroup (0x020ae3b0), provisional name Knife_Comm_removePlayerFromGroup. Next to the
// group word helpers of knifecomm.cpp (Knife_Comm_setPlayerBit at 0x020ae358).

// Group word: player mask (bits 0-3), group type (bits 4-6), complete flag (bit 7)
typedef struct KnifeGroupWordF {
    u32 playerMask : 4;
    u32 groupType : 3;
    u32 complete : 1;
    u32 unk : 24;
} KnifeGroupWordF;

// Knife_Comm_removePlayerFromGroup(playerNo, groupWord) (0x020ae3b0, provisional name): playerNo 0 clears the player mask
// and the group type. Otherwise the player's bit is cleared in the player mask; when the group is complete (bit 7), the
// AIDs of the four slots are reordered so that the removed player's slot is last, and the group type is set from the
// conversion map of the remaining players.
void Knife_Comm_removePlayerFromGroup(s32 playerNo, u32 *groupWord) {
    KnifeGroupWordF *g;
    u32 arr[4];
    s32 count;
    s32 slot;
    s32 i;
    u32 mask;

    g = (KnifeGroupWordF *)groupWord;
    if (playerNo == 0) {
        g->playerMask = 0;
        g->groupType = 0;
        return;
    }
    count = MATH_CountPopulation(g->playerMask);
    slot = Knife_Comm_GetPlayerNoByAID(playerNo, groupWord);
    mask = g->playerMask & ~(1u << playerNo);
    g->playerMask = mask;
    if (g->complete == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        arr[i] = Knife_Comm_GetAIDByPlayerNo(i, groupWord);
    }
    while (slot < count - 1) {
        u32 tmp = arr[slot];
        arr[slot] = arr[slot + 1];
        arr[slot + 1] = tmp;
        slot++;
    }
    g->groupType = Knife_Comm_GetAIDConvMap(count - 1, (s32 *)arr);
}
