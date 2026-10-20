#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0b, original name Em0b):
//   Em0b

// Main of em0b: the same check of the counter as Em0a, then the handler of the current action.
ARM void Em0b(Entity *e) {
    if (*(u16 *)(data_0212c540 + 2) > 1) {
        func_02084700(e);
    }
    data_020cfddc[e->action](e);
}
