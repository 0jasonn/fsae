#include "engine/functions.h"
#include "global.h"
#include "object/kumo_big.h"

// kumo_big family (module kumo_big), 0x0206d610 .. 0x0206d704.
// Address -> name: 0x0206d610 kumo_big0, 0x0206d62c kumo_big0_init, 0x0206d678 kumo_big0_move,
// 0x0206d6b0 kumo_big1, 0x0206d6cc kumo_big1_move

ARM void kumo_big0(Entity *e) {
    kumoBig0Table[e->action](e);
}

ARM void kumo_big0_init(Entity *e) {
    u8 nextAction = e->action + 1;

    e->action = nextAction;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    e->timer = 0x1e;
    set_pos(e);
    InitAnimationForceUpdate(e, e->type);
}

ARM void kumo_big0_move(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->x.HALF.HI -= 2;
    if (e->x.HALF.HI > -0x78) {
        return;
    }
    PutObjWork(e);
}

ARM void kumo_big1(Entity *e) {
    kumoBig1Table[e->action](e);
}

ARM void kumo_big1_move(Entity *e) {
    if (e->timer != 0) {
        e->timer--;
        return;
    }
    e->x.HALF.HI += 2;
    if (e->x.HALF.HI < 0x198) {
        return;
    }
    PutObjWork(e);
}
