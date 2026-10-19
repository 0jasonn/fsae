#include "engine/functions.h"
#include "object/coin.h"
#include "global.h"

// Coin actor, continued. Address -> name:
//   0x02058948 kirakira_set (original name)
//   0x020589b0 coin_move (original name)
//   0x02058a64 coin_wait (original name)

ARM void kirakira_set(Entity *e) {
    Entity *child;
    if ((data_0212c594 & 7) != 0) {
        return;
    }
    child = GetSetWork(0xd, 0xa, 0);
    if (child == NULL) {
        return;
    }
    child->x.HALF.HI = e->x.HALF.HI + (Random() & 7) - 3;
    child->y.HALF.HI = e->y.HALF.HI + (Random() & 7) - 3;
}

ARM void coin_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (e->y.HALF.HI > 0x34) {
        e->action++;
        InitAnimationForceUpdate(e, 1);
        data_0212ceb0[e->type2].state = 4;
        data_0212ceb0[e->type2].stateTimer = 0xff;
        SoundReq(0x216);
        SoundReq(0x216 - 0x73);
    }
    kirakira_set(e);
    e->spriteSettings.b16 = ((data_0212c594 & 2) == 0) ? 0 : 3;
}

ARM void coin_wait(Entity *e) {
    kirakira_set(e);
    e->spriteSettings.b16 = ((data_0212c594 & 2) == 0) ? 0 : 3;
}
