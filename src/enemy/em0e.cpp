#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/em00.h"

// Functions in this file (actor em0e, original names from the debug build):
//   Em0e, em0e_type0

// Main of em0e: runs the handler of the entity's type.
ARM void Em0e(Entity *e) {
    data_020cfec8[e->type](e);
}

// State handler of the type 0 variant: runs the handler of the current action.
ARM void em0e_type0(Entity *e) {
    data_020cfe94[e->action](e);
}
