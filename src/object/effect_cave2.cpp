#include "engine/functions.h"
#include "global.h"
#include "object/effect_cave2.h"

// effect_cave2 family (module effect_cave2), 0x0206ddc8 .. 0x0206de60.
// Address -> name: 0x0206ddc8 effect_cave2, 0x0206dde4 effect_cave2_move

ARM void effect_cave2(Entity *e) {
    effectCave2Table[e->action](e);
}

ARM void effect_cave2_move(Entity *e) {
    u8 timer;

    if (e->subtimer == 0) {
        e->spriteSettings.b0 = 1;
    } else {
        e->subtimer--;
        return;
    }
    UpdateAnimationSingleFrame(e);
    timer = e->timer;
    e->timer = timer - 1;
    if (timer == 0) {
        e->timer = 0x78;
        InitAnimationForceUpdate(e, e->type);
    }
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    PutObjWork(e);
}
