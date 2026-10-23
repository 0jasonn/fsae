#include "engine/functions.h"
#include "global.h"
#include "object/set66.h"

// Set68 actor (module set68). Address -> name:
//   0x02075610 Set68 (provisional name; dispatches on e->type)
//   0x0207562c set68_type0 (original name)
//   0x020756d8 set68_type1 (original name; dispatches on e->action)
//   0x020756f4 type01_init (original name)
//   0x0207573c type01_up (original name)
//   0x0207578c type01_wait (original name)
//   0x020757fc type01_center (original name)

ARM void Set68(Entity *e) {
    set68_typeActions[e->type](e);
}

ARM void set68_type0(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b14 = 1;
        e->spriteSettings.b30 = 1;
        e->unk_5e.b0 = 3;
        InitAnimationForceUpdate(e, 1);
    }
    UpdateAnimationSingleFrame(e);
    if (e->frame & 1) {
        e->frame = 0;
        e->timer = e->timer ^ 1;
        if (e->timer != 0) {
            SoundReq(0x21d);
        }
    }
    if (em12_typeMasks[0] & 1) {
        PutObjWork(e);
    }
}

ARM void set68_type1(Entity *e) {
    set68_type1Actions[e->action](e);
}

ARM void type01_init(Entity *e) {
    e->action = 1;
    e->subtimer = e->type2;
    e->speed = 0x280;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 3;
    InitAnimationForceUpdate(e, 3);
}

ARM void type01_up(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (!(em12_typeMasks[0] & 2)) {
        return;
    }
    MoveDir(e);
    if (e->y.HALF.HI > 0x104) {
        return;
    }
    e->y.HALF.HI = 0x104;
    e->action = 2;
    e->timer = 0x1e;
}

ARM void type01_wait(Entity *e) {
    s16 x;

    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 3;
    em12_typeMasks[0] = 4;
    x = e->x.HALF.HI;
    if (x > 0x1f8) {
        e->direction = 0x18;
        e->speed = (x - 0x1f8) << 1;
    } else {
        e->direction = 8;
        e->speed = (0x1f8 - x) << 1;
    }
}

ARM void type01_center(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->speed != 0) {
        MoveDir(e);
    }
    if (!(em12_typeMasks[0] & 8)) {
        return;
    }
    PutObjWork(e);
}
