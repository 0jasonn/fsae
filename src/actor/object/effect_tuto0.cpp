#include "engine/functions.h"
#include "global.h"
#include "actor/object/effect_tuto0.h"

// effect_tuto0 family (module effect_tuto0), 0x0206da58 .. 0x0206db30.
// Address -> name: 0x0206da58 effect_tuto0, 0x0206da74 effect_tuto0_init, 0x0206dadc effect_tuto0_move

void effect_tuto0(Entity *e) {
    effectTuto0Table[e->action](e);
}

// Effect tuto0 actor, init (module effect_tuto0). Address -> name:
//   0x0206da74 effect_tuto0_init (original name)
void effect_tuto0_init(Entity *e) {
    u32 settings = *(u32 *)&e->spriteSettings;
    int nextAction = e->action + 1;
    settings = (settings & ~0xc000) | 0xc000;
    settings = (settings & ~0xc0000000) | 0x40000000;
    *(u32 *)&e->spriteSettings = settings;
    e->action = nextAction;
    e->timer = 0x78;
    e->subtimer = 8;
    if (e->type == 0xa) {
        *(u32 *)&e->spriteSettings = (settings & ~0xc0000000) | 0x80000000;
    }
    set_pos(e);
    InitAnimationForceUpdate(e, e->type);
}

// effect_tuto0 family (module effect_tuto0), 0x0206dadc .. 0x0206db30 (effect_tuto0_init, 0x0206da74, is parked in scratch/agentA/nonmatching).
// Address -> name: 0x0206dadc effect_tuto0_move

void effect_tuto0_move(Entity *e) {
    if (e->subtimer == 0) {
        e->spriteSettings.b0 = 1;
    } else {
        e->subtimer--;
        return;
    }
    UpdateAnimationSingleFrame(e);
    if (e->type2 == KNIFE_CURSOR_INDEX()) {
        return;
    }
    PutObjWork(e);
}
