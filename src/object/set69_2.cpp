#include "engine/functions.h"
#include "global.h"
#include "object/set66.h"

// Set69 actor, second unit (module set69). Address -> name:
//   0x02075ca0 type0_waitkamae (original name)
//   0x02075d50 type0_wait2 (original name)

ARM void type0_waitkamae(Entity *e) {
    Entity *spawn;
    u8 i;

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 7;
    e->timer = 0x96;
    em12_typeMasks[0] = 0;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        spawn = GetSetWork(0x68, 0, 0);
        if (spawn != NULL) {
            ObjPosCopyOfs32(data_0212ceb0[i].entity, spawn, 0xa0000, -0x100000);
        }
    }
}

ARM void type0_wait2(Entity *e) {
    Entity *spawn;
    u8 i;

    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 8;
    e->timer = 0x3c;
    em12_typeMasks[0] = 1;
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        spawn = GetSetWork(0x68, 1, i);
        if (spawn != NULL) {
            ObjPosCopyOfs32(data_0212ceb0[i].entity, spawn, 0xa0000, -0x100000);
        }
    }
    SoundReq(0x21c);
}

ARM void type0_wait3(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 9;
    e->direction = 0;
    em12_typeMasks[0] = 2;
}

ARM void type0_up(Entity *e) {
    MoveDir(e);
    if (e->y.HALF.HI > 0x118) {
        return;
    }
    e->y.HALF.HI = 0x118;
    e->action = 10;
    e->timer = 0x64;
}
