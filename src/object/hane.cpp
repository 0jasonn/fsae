#include "engine/functions.h"
#include "game/stageseldecls.h"

// haneSet, 0x0207c5d8. Creates the wing object (type 0x24) at the position of e, linked to e, and marks it as a
// child when e has the layer bit 0x4000.
ARM void haneSet(Entity *e) {
    Entity *child = GetSetWork(0x24, 0, 0);
    if (child == 0) {
        return;
    }
    child->x.HALF.HI = e->x.HALF.HI;
    child->y.HALF.HI = e->y.HALF.HI;
    child->contactedEntity = e;
    func_0208ae30(child);
    if ((e->layer & 0x4000) == 0) {
        return;
    }
    if ((child->layer & 0x8000) == 0) {
        return;
    }
    child->layer = child->layer & 0x7fff;
    child->layer = child->layer | 0x4000;
}
