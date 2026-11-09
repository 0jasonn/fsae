#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// 0x0207c228 CalcRupeeDiff (original name): the largest amount by which a player's counter exceeds the stored
// value of the given type (0 when none does).

extern s32 data_0212c7d4[];

int CalcRupeeDiff(u8 index) {
    u32 base = data_0212c7d4[index];
    int best = 0;
    s8 i;
    for (i = 3; i >= 0; i--) {
        int diff = gameState.playerCounters[i] - base;
        if (diff > best) {
            best = diff;
        }
    }
    return best;
}
