#include "boss/boss_02038544.h"
#include "global.h"

ARM void func_02038a34(Entity *e) {
    func_020847a0(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    e->action = 5;
    e->speed -= 0x40;
    e->unk_5e.b0 = 2;
    InitAnimationForceUpdate(e, 4);
}

ARM void func_02038a88(Entity *e) {
    if (e->unk_60 == 0) {
        return;
    }
    Entity *n = e->parent;
    if (n == 0) {
        return;
    }
    if (e->type2 == 1) {
        e->unk_64[4] = 0;
        n->type2 = 0;
    }
}

ARM void func_02038ab4(Entity *e) {
    EnemyFunctionHandler(e, data_020d195c);
}

ARM void func_02038ac8(Entity *e) {
    data_020d18bc[e->action](e);
}

ARM void func_02038ae4(Entity *e) {
    if (e->action == 3) {
        e->action = 1;
        e->speed = 0x80;
        e->subtimer = 0x14;
    }
    GenericKnockback(e, data_020d195c);
}

ARM void func_02038b1c(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 2;
    e->hitbox = data_020d18b4;
    InitAnimationForceUpdate(e, 0);
    e->animationState = 0;
    e->action++;
}
