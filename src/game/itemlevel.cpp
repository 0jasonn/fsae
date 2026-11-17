#include "engine/functions.h"
#include "game/itemlevel.h"
#include "global.h"

// CalcItemLevel (0x0207c26c): picks the item level of the players. In a single-player game one random byte below 8
// gives level 1 or 2 (by its low bit), otherwise 0, for both slots. In a wireless game each player's rupee gain is
// compared with the thresholds of the current row; the number of thresholds reached (at most 7) is the level.
void CalcItemLevel(void) {
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
        u32 value = Random() & 0xff;
        u8 level;
        if (value < 8) {
            level = (value & 1) + 1;
        } else {
            level = 0;
        }
        gameState.unk_50[4] = gameState.unk_50[5] = level;
        return;
    }
    u8 player;
    for (player = 0; player < gameState.playerCount; player++) {
        int gain = CalcRupeeDiff(player);
        const u16 *threshold = &data_02117b20[gameState.unk_01 * 8];
        u8 level = 0;
        do {
            if (threshold[0] > gain) {
                break;
            }
            level++;
            threshold++;
        } while (level < 7);
        if (level > 7) {
            level = 7;
        }
        gameState.unk_50[4 + player] = level;
    }
}
