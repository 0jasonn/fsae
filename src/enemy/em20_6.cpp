#include "engine/functions.h"
#include "global.h"
#include "enemy/em20.h"
#include "enemy/em20_6.h"

// Functions in this file: em20_init (0x0203e854).

ARM void em20_init(Entity *e) {
    s32 dir;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->hitbox = em20_hitbox;
    VARS(Vars_em20, e)->phase = Random();
    VARS(Vars_em20, e)->lastDirection = 0xff;
    dir = Random() & 0x18;
    e->direction = dir;
    e->animationState = dir >> 3;
    InitAnimationForceUpdate(e, e->animationState);
}
