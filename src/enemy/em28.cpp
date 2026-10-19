#include "engine/functions.h"
#include "enemy/em26.h"
#include "global.h"

ARM void em28_init(Entity *e) {
    Entity *child = GetTamaWork2(9);
    if (child == NULL) {
        return;
    }
    child->parent = e;
    e->child = child;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->statusFlags |= 0x80;
    e->hitbox = em28_hitbox;
    e->timer = 0x64;
    em28_claim.claimed = 0;
    em28_claim.unk_4 = 0;
    InitAnimationForceUpdate(e, 0);
}

ARM void em28_getdir(Entity *e) {
    e->action = 2;
    e->timer = 0x3c;
    e->unk_6c[8] = 0x3c;
    e->subtimer = 4;
    e->direction = Random() & 0x18;
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, e->animationState);
}
