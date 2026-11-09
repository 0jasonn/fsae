#include "engine/functions.h"
#include "actor/object/tama06.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x0207f0cc tama06_rlarge (original name): turns the piece around its parent for 0x80 frames, then returns to action 1.

void tama06_rlarge(Entity *e) {
    type0PosSetR(e, e->timer >> 3);
    e->direction = (e->direction - 1) & 0x1f;
    e->timer++;
    if (e->timer >= 0x80) {
        e->action = 1;
        e->parent->subtimer = 0;
    }
}
