#include "enemy/em26.h"
#include "global.h"

ARM void em28_init(Entity *e) {
    Entity *c = GetTamaWork2(9);
    if (c == NULL) {
        return;
    }
    c->parent = e;
    e->child = c;
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 5;
    e->unk_3c |= 0x80;
    e->hitbox = data_020d32d4;
    e->timer = 0x64;
    data_021348cc.unk_0 = 0;
    data_021348cc.unk_4 = 0;
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
