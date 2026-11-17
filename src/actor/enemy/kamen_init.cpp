#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/kamen_init.h"

// Functions in this file: kamen_init (0x0203ecb8).

void kamen_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 4;
    e->statusFlags = 0;
    e->speed = 0x100;
    e->zVelocity = 0x12000;
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, e->animationState + 8);
}
