#include "engine/functions.h"
#include "game/gamestateview_c.h"
#include "global.h"
#include "types.h"

// CalcHeartLevel (0x0207c334): picks the heart level of the stage from the lowest counter among the players
// (tier 0..3 by the counter), indexed by the level row and the pick index, and stores it at game state 0x4d.
// Level row 0x4d is unk_49[4] of GameStateView (heart level result; proposed as heartLevel in the report).

// Level table: one row of four bytes per level, one table per pick index
extern const u8 *const data_02117a0c[];

extern "C" void CalcHeartLevel(void);
ARM void CalcHeartLevel(void) {
    u8 playerCount;
    u8 level;
    u8 i;
    u16 minCounter;
    u8 j;
    u8 tier;
    const u8 *row;

    level = data_0212c7c8.difficulty - 1;
    playerCount = data_0212c7c8.playerCount;
    i = 0;
    while (i < playerCount) {
        if (data_0212c7c8.slots[i].fieldBits != 0x3f) {
            break;
        }
        i++;
    }
    if (i == playerCount) {
        level++;
    }

    minCounter = 0xffff;
    for (j = 0; j < playerCount; j++) {
        if (minCounter > data_0212c7c8.slots[j].counter) {
            minCounter = data_0212c7c8.slots[j].counter;
        }
    }

    if (minCounter == 0) {
        tier = 0;
    } else if (minCounter < 6) {
        tier = 1;
    } else if (minCounter < 0xb) {
        tier = 2;
    } else {
        tier = 3;
    }

    row = data_02117a0c[data_0212c7c8.pickIndex] + level * 4;
    data_0212c7c8.unk_49[4] = row[tier];
}
