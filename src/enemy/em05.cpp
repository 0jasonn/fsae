#include "engine/functions.h"
#include "enemy/em03.h"
#include "global.h"

ARM void em05_stop(Entity *e) {
    func_02084f54(e);
    if (e->unk_43 == 0) {
        e->poseId = V(e)->savedUnk3f;
    }
}

ARM void em05_init(Entity *e) {
    if (e->type != 0) {
        e->poseId = 9;
    }
    e->spriteSettings.b0 = 1;
    e->unk_2e = 6;
    V(e)->initHealth = e->health;
    e->hitbox = em05_hitbox;
    if (e->type == 3) {
        e->subtimer = (Random() & 0x7f) + 0x40;
    }
    e->action++;
    e->timer = 1;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
    em05DirChange(e);
}

ARM void em05_move0(Entity *e) {
    if (--e->timer == 0) {
        e->timer = (Random() & 0x1c) + 0x1e;
        em05DirChange(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

ARM void em05_jump0(Entity *e) {
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1100) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, e->animationState + 6);
}
