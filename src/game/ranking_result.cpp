#include "engine/functions.h"
#include "sdk/fx/fx.h"
#include "engine/effect_state.h"
#include "engine/player.h"
#include "engine/cockpit_state.h"
#include "game/rankingsave.h"

// Functions in this file (original names from the debug build): make_cockpit, calc_result

// make_cockpit() (0x02055328): draws the ranking scene's HUD page: clears both pages, puts the 2x2 rupee icon at row
// 0x16, column 0x18 and writes the group's score (at most 99999) as five digits next to it.
void make_cockpit(void) {
    u16 *icon;
    u32 score;
    u16 tile;

    cockpitState.redraw = 1;
    cockpitState.bufferIndex = 0;
    MIi_CpuClearFast(0, data_021361a0, 0x1000);
    tile = 0x201c;
    icon = (u16 *)data_021361a0[cockpitState.bufferIndex] + 0x2d8;
    icon[0] = tile;
    score = gameState.score;
    icon[1] = tile + 1;
    icon[0x20] = tile + 2;
    icon[0x21] = tile + 3;
    ranking_write_rupee((u16 *)data_021361a0[cockpitState.bufferIndex] + 0x2de, score >= 99999 ? 99999 : score, 5,
                        0x3000);
    func_02026774();
}

// calc_result() (0x020553d4): computes each player's ranking value, sqrt(score) * player's count / score (score in
// gameState, counts in gameState.playerCounters), into effectState.rankValues; all four are 0 when the score is 0.
// The wireless and single-cart arms compute the same thing; they are kept apart (the ROM has two copies), the cast
// in the second arm stops mwcc from merging them.
void calc_result(void) {
    u32 root;
    u16 *values = effectState.rankValues;

    if (gameState.score == 0) {
        values[0] = 0;
        values[1] = 0;
        values[2] = 0;
        values[3] = 0;
        return;
    }
    root = (u32)(FX_Sqrt(gameState.score << 12) << 4) >> 16;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        values[0] = root * gameState.playerCounters[0] / gameState.score;
        values[1] = root * gameState.playerCounters[1] / gameState.score;
        values[2] = root * gameState.playerCounters[2] / gameState.score;
        values[3] = root * gameState.playerCounters[3] / gameState.score;
    } else {
        values[0] = root * gameState.playerCounters[0] / (u32)gameState.score;
        values[1] = root * gameState.playerCounters[1] / (u32)gameState.score;
        values[2] = root * gameState.playerCounters[2] / (u32)gameState.score;
        values[3] = root * gameState.playerCounters[3] / (u32)gameState.score;
    }
}
