#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em19.h"
#include "actor/enemy/em19_4.h"
// functions.h declares func_02084ac8/func_02084ae8 as returning u32; the ROM passes the result on without an and-mask,
// so the original return type is u8 (proposed shared change). Until functions.h is changed these calls go through
// a function pointer type with the u8 return.
typedef u8 (*Em19DirQuery)(Entity *e, int a);
typedef u8 (*Em19DirQueryTarget)(Entity *e, int a, Entity *target);

void em19_wait(Entity *e) {
    if (VARS(Vars_em19, e)->waitTimer != 0) {
        VARS(Vars_em19, e)->waitTimer--;
        return;
    }
    if (FindTargetInRange(e, 0x68, 0x48) == NULL) {
        if (VARS(Vars_em19, e)->moveTimer != 0) {
            VARS(Vars_em19, e)->moveTimer--;
            return;
        }
        VARS(Vars_em19, e)->moveTimer = 0x3c;
        if ((Random() & 0x1f) != 0) {
            return;
        }
        e->action = 2;
        e->spriteSettings.b0 = 1;
        e->animationState = 0;
        InitAnimationForceUpdate(e, 0);
    } else {
        u8 r = ((Em19DirQuery)func_02084ac8)(e, 0xe);
        if ((r & 0x80) != 0) {
            e->spriteSettings.b0 = 1;
            bgobj_moveset(e, r);
        }
    }
}

void em19_kyorokyoro(Entity *e) {
    u8 r;
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        r = ((Em19DirQueryTarget)func_02084ae8)(e, 0xe, e->child);
        if ((r & 0x80) != 0) {
            bgobj_moveset(e, r);
        }
    } else {
        waitset(e);
    }
}

