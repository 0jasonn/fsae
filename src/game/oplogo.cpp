#include "engine/functions.h"
#include "global.h"

// Opening logo objects, 0x02068044 to 0x0206829c. Names for func_ symbols: scratch/agentA/renames.txt.
extern EntityFunc oplogo_shadowTable[];
extern u8 data_0212c4dc;

ARM void oplogo_sword_test0(Entity *e) {
    switch (e->timer) {
    case 0x3a:
        GetSetWork(0x28, 0xa, 0);
        break;
    case 0x35:
        GetSetWork(0x28, 0xa, 1);
        break;
    case 0x2e:
        GetSetWork(0x28, 0xa, 2);
        break;
    case 0x26:
        GetSetWork(0x28, 0xa, 3);
        break;
    }
    if (e->timer-- != 0) {
        return;
    }
    e->action++;
    e->direction = 8;
    e->speed = 0x200;
}

ARM void oplogo_sword_test1(Entity *e) {
    MoveDir(e);
    e->speed -= 0x10;
    if (e->speed <= 0) {
        e->action++;
        e->timer = 0;
    }
}

ARM void oplogo_sword_wait(Entity *e) {
    Entity *sword;
    if (e->timer-- != 0) {
        return;
    }
    e->action++;
    e->direction = 0x18;
    e->speed = 0x800;
    sword = GetSetWork(0x28, 2, 0);
    sword->x.HALF.HI = e->x.HALF.HI;
    sword->y.HALF.HI = e->y.HALF.HI;
    sword = GetSetWork(0x28, 2, 1);
    sword->x.HALF.HI = e->x.HALF.HI;
    sword->y.HALF.HI = e->y.HALF.HI;
    sword = GetSetWork(0x28, 2, 2);
    sword->x.HALF.HI = e->x.HALF.HI;
    sword->y.HALF.HI = e->y.HALF.HI;
    GetSetWork(0x28, 3, 0);
    SoundReq(0x209);
}

ARM void oplogo_sword_left(Entity *e) {
    MoveDir(e);
    if (e->x.HALF.HI >= 0x50) {
        return;
    }
    e->x.HALF.HI = 0x50;
    e->action++;
    e->timer = 5;
}

ARM void oplogo_sword_end(Entity *e) {
    if (--e->timer != 0) {
        return;
    }
    FadeSet(2, 8);
    GetSetWork(0x28, 0, 0);
    PutObjWork(e);
    data_0212c4dc++;
    SoundReq(0x20a);
    SoundReq(0x1b2);
}

ARM void oplogo_shadow(Entity *e) {
    oplogo_shadowTable[e->action](e);
}
