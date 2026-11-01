#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj_6.h"
#include "enemy/bgobj.h"

// Functions in this file: bgobj_init (0x0203e59c), bgobj_move (0x0203e610).

// Bytes of the bgobj work area after the shared Entity fields (0x68..0x6d).
typedef struct BgobjVars {
    u8 unk_00[0x68];
    u8 unk_68;
    u8 unk_69;
    u8 unk_6a;
    u8 unk_6b;
    u16 unk_6c;
} BgobjVars;

// bgobj_init (0x0203e59c): creates the child object (GetEnemyWork(0x19)) and links the two.
void bgobj_init(Entity *e) {
    Entity *child;

    child = GetEnemyWork(0x19);
    if (child == 0) {
        return;
    }
    EmPalamCopy(e, child);
    e->linkedEntity = 0;
    VARS(BgobjVars, e)->unk_68 = 0;
    VARS(BgobjVars, e)->unk_69 = 0;
    VARS(BgobjVars, e)->unk_6b = 0;
    VARS(BgobjVars, e)->unk_6c = 0;
    child->type = 2;
    child->parent = e;
    e->parent = child;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_1a = 0;
    InitAnimationForceUpdate(e, 0);
}

// bgobj_move (0x0203e610): runs the moving object (func_02089524) while the entity and its parent are alive.
void bgobj_move(Entity *e) {
    if (e->health != 0 && e->parent->health != 0) {
        func_02089524(e);
        return;
    }
    PutObjWork(e);
}

// Functions in this file: bgobj_lift (0x0203e63c).

void bgobj_lift(Entity *e) {
    bgobj_liftTable[e->subAction](e);
}

// Functions in this file: bgobj_lift_init (0x0203e658), bgobj_lift_nop1 (0x0203e69c, empty state 1).

void bgobj_lift_init(Entity *e) {
    e->subAction = 1;
    e->unk_2e = 2;
    if (e->parent->health == 0) {
        return;
    }
    e->parent->action = 7;
    e->parent->parent = 0;
    e->parent->zVelocity = 0x18000;
}

void bgobj_lift_nop1(Entity *e) {
}

// Functions in this file: bgobj_lift_throw (0x0203e6a0), bgobj_lift_nop3 (0x0203e6c4, empty state 3).

void bgobj_lift_throw(Entity *e) {
    if (e->z.HALF.HI == 0) {
        effectset(e);
        PutObjWork(e);
    }
}

void bgobj_lift_nop3(Entity *e) {
}

// Functions in this file: bgobj_poscopy (0x0203e6c8).

void bgobj_poscopy(Entity *e) {
    if (e->spriteSettings.b0 != 0) {
        ObjPosCopyOfs32(e, e->parent, 0, 0x10000);
        e->parent->z.HALF.HI = bgobj_poscopyTable[(e->animationState << 1) + (e->frame & 1)];
    } else {
        ObjPosCopy(e, e->parent);
    }
}

// Functions in this file: bgobj_moveset (0x0203e720).

void bgobj_moveset(Entity *e, u8 direction) {
    e->action = 3;
    e->direction = direction & 0x1f;
    e->timer = bgobj_moveTimerTable[Random() & 3];
    e->animationState = 2;
    InitAnimationForceUpdate(e, 2);
}
