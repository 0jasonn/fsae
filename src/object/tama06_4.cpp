#include "engine/functions.h"
#include "object/tama06.h"

// tama06 family, type0 position helpers, address -> name (original names from symbols.txt):
//   0x0207f31c type0PosSet, 0x0207f3f0 type0WaitPosSet, 0x0207f434 type0AttackPosSet

// type0WaitPosSet, 0x0207f3f0. Places the piece at the parent's position plus the offset of its animation.
ARM void type0WaitPosSet(Entity *e) {
    e->x.HALF.HI = e->parent->x.HALF.HI + data_020dce0c[e->parent->animationState * 2];
    e->y.HALF.HI = e->parent->y.HALF.HI + data_020dce0c[e->parent->animationState * 2 + 1];
}

// type0AttackPosSet, 0x0207f434. Moves the piece by how far the parent moved since the last call, then saves the
// parent's position.
ARM void type0AttackPosSet(Entity *e) {
    e->x.HALF.HI = e->x.HALF.HI + (s16)(e->parent->x.HALF.HI - (u16)VARS(Vars_Tama06Move, e)->targetX);
    e->x.HALF.HI = e->x.HALF.HI + (s16)(e->parent->y.HALF.HI - (u16)VARS(Vars_Tama06Move, e)->targetY);
    VARS(Vars_Tama06Move, e)->targetX = e->parent->x.HALF.HI;
    VARS(Vars_Tama06Move, e)->targetY = e->parent->y.HALF.HI;
}
