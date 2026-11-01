#include "engine/functions.h"
#include "actor/object/taimatsu.h"
#include "global.h"

// Taimatsu puzzle actor (module taimatsu). Address -> name:
//   0x02059678 taimatsu_puzzle_00 (original name)

void taimatsu_puzzle_00(Entity *e) {
    taimatsu00_actions[e->action](e);
}
