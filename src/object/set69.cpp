#include "engine/functions.h"
#include "global.h"
#include "object/set66.h"

// Set69 actor (module set69). Address -> name:
//   0x02075a60 Set69 (provisional name; dispatches on e->type)
//   0x02075a7c set69_type0 (original name; dispatches on e->action, then BindPlayers)
//   0x02075a9c rr_type0_init_075a9c (dsd name, original type0_init)
//   0x02075aec set69_type0_follow (provisional name; sets action 2 and copies position to the parent)
//   0x02075b04 type0_scrWait (original name)
//   0x02075b58 type0_kameradown (original name)
//   0x02075ba0 type0_wait0 (original name)

ARM void Set69(Entity *e) {
    set69_typeActions[e->type](e);
}

ARM void set69_type0(Entity *e) {
    set69_type0Actions[e->action](e);
    BindPlayers();
}

ARM void rr_type0_init_075a9c(Entity *e) {
    e->action = 1;
    e->speed = 0x180;
    e->direction = 0x10;
    e->x.HALF.HI = 0x1f8;
    e->y.HALF.HI = 0x148;
    *(Entity **)data_0212c648 = e;
    InitAnimationForceUpdate(e, 0);
    rr_plset(e);
}

ARM void set69_type0_follow(Entity *e) {
    e->action = 2;
    ObjPosCopy(e, e->parent);
}

ARM void type0_scrWait(Entity *e) {
    if (e->x.HALF.HI == *(s16 *)(data_0212c648 + 0x20) + 0x80 &&
        e->y.HALF.HI == *(s16 *)(data_0212c648 + 0x22) + 0x60) {
        FadeSet(2, 2);
        e->action = 3;
        e->timer = 0xf8;
    }
}

ARM void type0_kameradown(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    MoveDir(e);
    if (e->y.HALF.HI < 0x1a8) {
        return;
    }
    e->y.HALF.HI = 0x1a8;
    e->action = 4;
    e->timer = 0x1e;
}

ARM void type0_wait0(Entity *e) {
    u8 i;

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 5;
    e->timer = 0x3c;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        data_0212ceb0[i].entity->animationState = 4;
    }
}
