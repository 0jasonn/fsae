#include "engine/functions.h"
#include "global.h"
#include "object/effect_tori.h"

// effect_tori family (module effect_tori), 0x0206db30 .. 0x0206dbe0.
// Address -> name: 0x0206db30 effect_tori, 0x0206db6c effect_tori_init, 0x0206dbb0 effect_tori_move

ARM void effect_tori(Entity *e) {
    effectToriTable[e->action](e);
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    PutObjWork(e);
}

ARM void effect_tori_init(Entity *e) {
    u32 settings = *(u32 *)&e->spriteSettings;
    u8 action = e->action;
    int nextAction;

    settings = (settings & ~0xc000) | 0x4000;
    settings = (settings & ~0xc0000000) | 0x40000000;
    settings &= ~3;
    nextAction = action + 1;
    e->action = nextAction;
    *(u32 *)&e->spriteSettings = settings | 1;
    e->timer = 0xf0;
    InitAnimationForceUpdate(e, e->type);
}

ARM void effect_tori_move(Entity *e) {
    u8 timer;

    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    timer = e->timer;
    e->timer = timer - 1;
    if (timer == 0) {
        e->type2 = 0xff;
    }
}
