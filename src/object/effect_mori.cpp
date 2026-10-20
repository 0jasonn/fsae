#include "engine/functions.h"
#include "global.h"
#include "object/effect_mori.h"

// effect_mori family (module effect_mori), 0x0206dbe0 .. 0x0206dcc8 (birdSet, 0x0206dcc8, is parked in scratch/agentA/nonmatching).
// Address -> name: 0x0206dbe0 effect_mori, 0x0206dc1c effect_mori_init, 0x0206dc6c effect_mori_wait

ARM void effect_mori(Entity *e) {
    effectMoriTable[e->action](e);
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    PutObjWork(e);
}

ARM void effect_mori_init(Entity *e) {
    u32 settings = *(u32 *)&e->spriteSettings;
    u8 action = e->action;
    int nextAction;

    settings = (settings & ~0xc000) | 0x8000;
    settings &= ~0xc0000000;
    nextAction = action + 1;
    e->action = nextAction;
    *(u32 *)&e->spriteSettings = settings | 0x40000000;
    e->timer = 1;
    e->subtimer = 8;
    set_pos(e);
    InitAnimationForceUpdate(e, e->type);
}

ARM void effect_mori_wait(Entity *e) {
    u8 timer;

    if (e->subtimer == 0) {
        e->spriteSettings.b0 = 1;
    } else {
        e->subtimer--;
        return;
    }
    timer = e->timer;
    e->timer = timer - 1;
    if (timer == 0) {
        e->timer = 0x10;
        e->action++;
        birdSet(e);
    }
}
