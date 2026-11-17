#include "engine/functions.h"
#include "actor/object/tama06.h"

// tama06 family, type0 position helpers, address -> name (original names from symbols.txt):
//   0x0207f37c type0PosSetR, 0x0207f3f0 type0WaitPosSet, 0x0207f434 type0AttackPosSet

// Positions the piece around its parent using the supplied radius and direction.
void type0PosSetR(Entity *e, u8 radius) {
    s32 scale;
    s32 product;
    s8 scaledRadius;

    scale = data_020dce54[e->direction];
    product = scale * radius;
    scaledRadius = product / 16;
    e->x.HALF.HI = e->parent->x.HALF.HI + ((scaledRadius * trigTable[e->direction * 8]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - 8 - ((scaledRadius * trigTable[e->direction * 8 + 0x40]) >> 8);
}

// type0WaitPosSet, 0x0207f3f0. Places the piece at the parent's position plus the offset of its animation.
void type0WaitPosSet(Entity *e) {
    e->x.HALF.HI = e->parent->x.HALF.HI + data_020dce0c[e->parent->animationState * 2];
    e->y.HALF.HI = e->parent->y.HALF.HI + data_020dce0c[e->parent->animationState * 2 + 1];
}

// type0AttackPosSet, 0x0207f434. Moves the piece by how far the parent moved since the last call, then saves the
// parent's position.
void type0AttackPosSet(Entity *e) {
    e->x.HALF.HI = e->x.HALF.HI + (s16)(e->parent->x.HALF.HI - (u16)VARS(Vars_Tama06Move, e)->targetX);
    e->x.HALF.HI = e->x.HALF.HI + (s16)(e->parent->y.HALF.HI - (u16)VARS(Vars_Tama06Move, e)->targetY);
    VARS(Vars_Tama06Move, e)->targetX = e->parent->x.HALF.HI;
    VARS(Vars_Tama06Move, e)->targetY = e->parent->y.HALF.HI;
}
