#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "game/clearkey.h"
#include "game/clearkey_level.h"

// ClearKeyLevelCheck (0x02048de8): checks the slots of all players. A player without slot flag 8 gives 1 at once.
// Otherwise the key bits of every player are combined per level; level 1 incomplete gives 1, level 2 incomplete
// gives 2, and when everybody carries the 0x800000 flag too the result is 3 (else 2).
int ClearKeyLevelCheck(void) {
    u8 keys;
    u32 all1;
    u32 all2;
    u32 all3;
    u8 missing;
    u8 i;
    all1 = all2 = all3 = 0xf;
    missing = i = 0;
    for (i = 0; i < gameState.playerCount; i++) {
        if ((gameState.slots[i].flags & 8) == 0) {
            return 1;
        }
        if ((gameState.slots[i].flags & 0x800000) == 0) {
            missing++;
        }
        keys = gameState.slots[i].fieldBits;
        all1 &= key_check(keys, 1);
        all2 &= key_check(keys, 2);
        all3 &= key_check(keys, 3);
    }
    if (all1 != 7) {
        return 1;
    }
    if (all2 != 7) {
        return 2;
    }
    if (missing != 0) {
        return 2;
    }
    return 3;
}
