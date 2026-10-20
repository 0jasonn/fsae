#include "engine/functions.h"
#include "global.h"
#include "object/set46.h"

// Set46 family (module set46), 0x0206d5c4 .. 0x0206d610.
// Address -> name: 0x0206d5c4 Set46, 0x0206d5e0 set_pos

ARM void Set46(Entity *e) {
    set46Table[e->type](e);
}

ARM void set_pos(Entity *e) {
    e->x.HALF.HI = set46PosTable[e->type * 2];
    e->y.HALF.HI = set46PosTable[e->type * 2 + 1];
}
