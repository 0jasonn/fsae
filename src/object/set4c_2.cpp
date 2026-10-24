#include "engine/functions.h"
#include "global.h"

// Set4c actor, second unit (module set4c). Address -> name:
//   0x0205e47c set4c_wait (original name)
//   0x0205e4d0 set4c_move (original name)
//   (set4c_init at 0x0205e3d4 is parked in scratch/agentC/nonmatching)

typedef struct Vars_Set4c {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 restFrames; // wait before the next activation
    /* 7a */ u16 activeFrames; // length of one activation
    /* 7c */ u16 activeCount; // countdown while active
    /* 7e */ u16 timer; // countdown of the wait state
} Vars_Set4c;

ARM void set4c_wait(Entity *e) {
    Vars_Set4c *v = VARS(Vars_Set4c, e);

    v->timer--;
    if (v->timer != 0) {
        return;
    }
    v->timer = v->restFrames;
    v->activeCount = v->activeFrames;
    e->action = 2;
    e->spriteSettings.b0 = 1;
    e->statusFlags |= 0x80;
}

ARM void set4c_move(Entity *e) {
    Vars_Set4c *v = VARS(Vars_Set4c, e);

    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        EnqueueSFX(0x7b);
    }
    if (v->activeCount != 0) {
        v->activeCount--;
        return;
    }
    if (!(e->frame & 0x80)) {
        return;
    }
    e->action = 1;
    e->spriteSettings.b0 = 0;
    e->statusFlags &= 0x7f;
}
