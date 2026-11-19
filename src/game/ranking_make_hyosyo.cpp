#include "actor/object/ranking5.h"
#include "engine/functions.h"
#include "engine/misc.h"
#include "engine/effect_state.h"
#include "game/rankingsave.h"
#include "engine/vgroup.h"
#include "engine/blend_request.h"
#include "engine/display_state.h"
#include "engine/map_state.h"
#include "engine/frame_counter.h"
#include "engine/vblank_request.h"
#include "engine/misc.h"
extern const u16 data_02115278[];

// make_hyosyo() (0x020558c0): sorts the ranking table by rank, frees the line slots and starts every player's result
// walk: the best player walks in with a sparkle, the others are placed on their rank's step.
void make_hyosyo(void) {
    s8 i;
    s8 j;
    s8 worstRank;
    u8 keyPlayer;
    u8 keyRank;
    u16 keyScore;
    RankingEntry *rk = data_02171d00;

    for (i = 8; i < 0x10; i++) {
        vgroupSlots[i].state = 0xff;
        vgroupSlots[i].link = 0xff;
    }
    for (i = 1; i < gameState.playerCount; i++) {
        keyPlayer = rk[i].playerIndex;
        keyRank = rk[i].rank;
        keyScore = rk[i].score;
        j = i - 1;
        while (j >= 0 && rk[j].rank > keyRank) {
            rk[j + 1].playerIndex = rk[j].playerIndex;
            rk[j + 1].rank = rk[j].rank;
            rk[j + 1].score = rk[j].score;
            j--;
        }
        rk[j + 1].playerIndex = keyPlayer;
        rk[j + 1].rank = keyRank;
        rk[j + 1].score = keyScore;
    }
    worstRank = rk[gameState.playerCount - 1].rank;
    for (i = 0; i < gameState.playerCount; i++) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
            if (rk[i].rank == 0) {
                DemoLinkWalkSet(rk[i].playerIndex, 0xff, 0);
                playerWork[rk[i].playerIndex].entity->y.HALF.HI = 0x178;
                if (gameState.score != 0 && gameState.active == 0) {
                    GetSetWork(0xd, 8, rk[i].playerIndex);
                }
            } else if (worstRank == rk[i].rank) {
                playerWork[rk[i].playerIndex].state = 7;
                playerWork[rk[i].playerIndex].entity->y.HALF.HI = data_02115278[gameState.playerCount * 3 + 2] + 0x178;
            } else {
                playerWork[rk[i].playerIndex].entity->y.HALF.HI = data_02115278[gameState.playerCount * 3 + rk[i].rank - 1] + 0x178;
            }
            GetSetWork(0xd, 9, (u8)(rk[i].playerIndex | (rk[i].rank << 4)));
        } else {
            playerWork[rk[i].playerIndex].state = (gameState.score >= 1000) ? 4 : 7;
            playerWork[rk[i].playerIndex].stateTimer = 0xff;
            playerWork[rk[i].playerIndex].unk_39 = 0;
            playerWork[rk[i].playerIndex].entity->y.HALF.HI = 0x178;
        }
    }
}
