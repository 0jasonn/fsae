#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0c, original name from the debug build):
//   Em0c

// Main of em0c: the same check of the counter as Em0a and Em0b, then the handler of the current action.
ARM void Em0c(Entity *e) {
    if (*(u16 *)(data_0212c540 + 2) > 1) {
        func_02084700(e);
    }
    data_020cfe10[e->action](e);
}
