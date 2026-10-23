#include "engine/functions.h"
#include "object/tama0f.h"

// tama0f family, address -> name (original names from symbols.txt):
//   0x0207db04 tama0f_fireshot, 0x0207db90 tama0f_post

// tama0f_fireshot, 0x0207db04. Counts down the fire timer and removes the actor at zero. Each time the subtimer runs
// out it aims at the player (timer is the player number) and restarts the subtimer.
ARM void tama0f_fireshot(Entity *e) {
    s32 fireTimer;
    u8 subtimer;
    if (e->parent->action == 4) {
        PutObjWork(e);
        return;
    }
    fireTimer = VARS(Vars_Tama0f, e)->fireTimer;
    VARS(Vars_Tama0f, e)->fireTimer = fireTimer - 1;
    if (fireTimer != 0) {
        UpdateAnimationSingleFrame(e);
        MoveDir(e);
        subtimer = e->subtimer;
        e->subtimer = subtimer - 1;
        if (subtimer == 0) {
            e->direction = func_02086078(e, data_0212ceb0[e->timer].entity);
            e->subtimer = 0x14;
        }
    } else {
        PutObjWork(e);
    }
}

// tama0f_post, 0x0207db90. Waits for the parent's action 4 to end; the state 6 removes the actor once its frame
// bit 7 is set, the other states count the subtimer and then start the matching animation.
ARM void tama0f_post(Entity *e) {
    u8 state;
    u8 subtimer;
    if (e->parent->action == 4) {
        PutObjWork(e);
        return;
    }
    UpdateAnimationSingleFrame(e);
    state = e->unk_23;
    if (state == 6) {
        if ((e->frame & 0x80) != 0) {
            PutObjWork(e);
        }
        return;
    }
    subtimer = e->subtimer;
    e->subtimer = subtimer - 1;
    if (subtimer != 0) {
        return;
    }
    if (state == 0xb) {
        e->statusFlags = e->statusFlags | 0x80;
        e->subtimer = 0x78;
        InitAnimationForceUpdate(e, 5);
        EnqueueSFX(0xb6);
        return;
    }
    e->statusFlags = e->statusFlags & 0x7f;
    InitAnimationForceUpdate(e, 6);
}
