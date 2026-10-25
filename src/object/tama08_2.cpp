#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/tama08_2.h"

// Tama08 family, second unit (module tama08). Address -> name:
//   0x0207f9dc tama08_move, 0x0207fa2c tama08_sasari, 0x0207fa58 tama08_kokin,
//   0x0207fa8c Tama09 (original name Tama09(OBJ_WORK_*)), 0x0207faf8 tama09_dispatch (invented, tama09_dispatch)

typedef struct Vars_Tama09 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u8 parentObjId;   // copied from the parent when the actor starts
    /* 71 */ u8 parentObjKind; // copied from the parent when the actor starts
} Vars_Tama09;

// Moves the actor, or bounces it off the wall when it is blocked
ARM void tama08_move(Entity *e) {
    if (func_0208b668(e) == 0) {
        e->action = 3;
        e->timer = 0x1e;
        e->statusFlags = 0;
        InitAnimationForceUpdate(e, e->animationState + 2);
    } else {
        func_0208af0c(e);
    }
}

// Counts the timer down and removes the actor when it runs out
ARM void tama08_sasari(Entity *e) {
    UpdateAnimationSingleFrame(e);
    e->timer = e->timer - 1;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}

// Moves the actor with gravity and removes it once it lands
ARM void tama08_kokin(Entity *e) {
    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1800) != 0) {
        return;
    }
    PutObjWork(e);
}

// Tama09, first frame copies the parent's object id and kind; then it follows the parent until the parent's
// contact flag is set, which makes the parent lose a little invincibility time
ARM void Tama09(Entity *e) {
    Entity *parent;

    parent = e->parent;
    if (e->action == 0) {
        e->action = 1;
        e->statusFlags = e->statusFlags | 0x20;
        VARS(Vars_Tama09, e)->parentObjId = parent->objId;
        VARS(Vars_Tama09, e)->parentObjKind = parent->objKind;
    }
    if (*(u32 *)&parent->unk_00[4] == 0) {
        PutObjWork(e);
        return;
    }
    if ((e->contactFlags & 0x80) == 0) {
        return;
    }
    if (parent->iframes == 0) {
        parent->iframes = 0xf4;
    }
}

// Runs the state table entry of the actor and removes it when its parent is gone (health 0)
ARM void tama09_dispatch(Entity *e) {
    data_020dcf90[e->action](e);
    if (e->parent->health != 0) {
        return;
    }
    HajikeSet(e);
    PutObjWork(e);
}
