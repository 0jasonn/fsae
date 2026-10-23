#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set66.h"

// Set66 type1 (module set66, third unit). Address -> name:
//   0x0207543c rr_type1_wait_07543c (dsd name, original type1_wait)
//   0x020754ac rr_type1_vanish (dsd name, original type1_vanish)
//   0x02075528 rr_poscopy (original name)
//   0x0207553c plStCheck (original name)

ARM void rr_type1_wait_07543c(Entity *e) {
    Vars_Set66 *v;
    Entity *spawn;

    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 4;
    v = VARS(Vars_Set66, e);
    v->vanishTimer = 0x168;
    spawn = GetSetWork(0x6b, 0, 0);
    if (spawn == NULL) {
        return;
    }
    spawn->type = e->type2;
    ObjPosCopy(data_0212ceb0[e->type2].entity, spawn);
}

ARM void rr_type1_vanish(Entity *e) {
    Vars_Set66 *v;

    UpdateAnimationSingleFrame(e);
    v = VARS(Vars_Set66, e);
    v->vanishTimer--;
    if (v->vanishTimer == 0) {
        VARS(Vars_Set66, e->parent)->typeBits ^= flagBits[e->type2];
        PutObjWork(e);
        return;
    }
    if (v->vanishTimer >= 0x3c) {
        return;
    }
    e->spriteSettings.b0 = e->spriteSettings.b0 ^ 1;
}

ARM void rr_poscopy(Entity *e, Entity *target) {
    target->x.WORD = e->x.WORD;
    target->y.WORD = e->y.WORD;
}
