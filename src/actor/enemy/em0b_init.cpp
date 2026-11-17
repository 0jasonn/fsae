#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em0b_init.h"

// Functions in this file: em0b_init (0x0202c260).

void em0b_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = em2b_hitbox;
    VARS(Vars_Em0bInit, e)->counter78 = 0;
    e->action++;
    if (e->type != 0) {
        e->speed = 0x400;
    }
    InitAnimationForceUpdate(e, 0);
}
