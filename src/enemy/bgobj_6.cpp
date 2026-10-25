#include "engine/functions.h"
#include "global.h"
#include "enemy/bgobj_6.h"

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
ARM void bgobj_init(Entity *e) {
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
ARM void bgobj_move(Entity *e) {
    if (e->health != 0 && e->parent->health != 0) {
        func_02089524(e);
        return;
    }
    PutObjWork(e);
}
