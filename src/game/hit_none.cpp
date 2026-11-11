#include "engine/functions.h"
#include "global.h"
#include "game/hitdecls.h"
#include "game/hit.h"

// Hit handler table (0x020ce540 and following) entries: no reaction, and a plain shield check.

// Handler 0: nothing happens and the hit is not consumed
BOOL hit_none(Entity *e, Entity *t, u8 mode) {
    return 0;
}

// Shield hit: lets the shield of e react to t, the hit is consumed
BOOL hit_shield(Entity *e, Entity *t, u8 mode) {
    shiledCheck(e, t);
    return 1;
}
