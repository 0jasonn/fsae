#include "Unknown/A/Boss_02038544.h"
#include "global.h"

ARM void func_02038da4(Entity *e) {
    func_02084f54(e);
    if (e->unk_43 == 0) {
        e->unk_3f = V(e)->unk_7c;
    }
}

ARM void func_02038dc4(Entity *e) {
    if (e->type != 0) {
        e->unk_3f = 9;
    }
    e->spriteSettings.b0 = 1;
    e->unk_2e = 6;
    V(e)->unk_7d = e->health;
    e->hitbox = data_020d19b8;
    if (e->type == 3) {
        e->subtimer = (Random() & 0x7f) + 0x40;
    }
    e->action++;
    e->timer = 1;
    e->animationState = 0;
    InitAnimationForceUpdate(e, 0);
    Boss_RandomizeDirection(e);
}

ARM void func_02038e54(Entity *e) {
    if (--e->timer == 0) {
        e->timer = (Random() & 0x1c) + 0x1e;
        Boss_RandomizeDirection(e);
    }
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
}

ARM void func_02038e9c(Entity *e) {
    func_020847c8(e);
    UpdateAnimationSingleFrame(e);
    if (UpdateGravity(e, 0x1100) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, e->animationState + 6);
}
