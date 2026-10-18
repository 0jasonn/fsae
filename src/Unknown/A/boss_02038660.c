#include "Unknown/A/Boss_02038544.h"
#include "global.h"

ARM void func_02038660(Entity *e) {
    e->unk_2e = 2;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    e->hitbox = data_020d1828;
    e->action++;
    e->timer = (Random() & 0x38) + 0x14;
    V(e)->unk_64 = func_02045eb4();
    e->direction = GetFacingDirection(e, V(e)->unk_64);
    InitAnimationForceUpdate(e, 0);
}

ARM void func_020386d8(Entity *e) {
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 1);
}

ARM void func_02038728(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame != 0x80) {
        return;
    }
    e->action++;
    e->zVelocity = 0x18000;
    InitAnimationForceUpdate(e, 2);
    if (func_0208de54(func_0208da4c()) == 0) {
        u8 p = *func_02093b5c();
        V(e)->unk_64 = data_0212ceb0[p].unk_28;
    }
    e->direction = func_02084fd0(e, V(e)->unk_64);
    func_02083c84(e);
    e->subAction = 0;
}

ARM void func_020387b4(Entity *e) {
    func_020847a0(e);
    UpdateGravity(e, 0x2000);
    if (e->subAction == 0) {
        e->subAction++;
        EnqueueSFX(0x31);
    }
    if (e->zVelocity < 0) {
        e->action++;
        InitAnimationForceUpdate(e, 3);
    }
}

ARM void func_02038810(Entity *e) {
    func_020847a0(e);
    if (UpdateGravity(e, 0x2000) != 0) {
        return;
    }
    e->action++;
    InitAnimationForceUpdate(e, 4);
}

ARM void func_0203884c(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame != 0x80) {
        return;
    }
    e->action = 1;
    e->timer = (Random() & 0x38) + 0x14;
    InitAnimationForceUpdate(e, 0);
}
