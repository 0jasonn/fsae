#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/enemy/decls_b2.h"

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
