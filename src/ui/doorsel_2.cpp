#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "ui/doorsel.h"
#include "engine/data_0212c500.h"

// doorsel_sync (0x0202ab90): advances the door select step data_0212c500 and clears the sub-step data_0212c4dc.
//   doorsel_sync (0x0202ab90)


void doorsel_sync(void) {
    data_0212c500 = data_0212c500 + 1;
    data_0212c4dc = 0;
}

// Position table lookup by player count: tables hold one (x, y) pair per player, with the entries for 2, 3 and 4 players
// stored one after another (2 pairs, then 3 pairs at +4 shorts, then 4 pairs at +10 shorts).
s16 *GetTablePlNum(s16 *table, u8 index) {
    switch (gameState.playerCount) {
    case 2:
    default:
        return table + index * 2;
    case 3:
        return table + 4 + index * 2;
    case 4:
        return table + 10 + index * 2;
    }
}
