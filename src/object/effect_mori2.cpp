#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"

// effect_mori2 family (module effect_mori2), 0x0206dfe4 .. 0x0206e054.
// Address -> name: 0x0206dfe4 effect_mori2, 0x0206e000 effect_mori2_move

// Action table of effect_mori2, effectMori2Table
extern const EntityFunc effectMori2Table[];

ARM void effect_mori2(Entity *e) {
    effectMori2Table[e->action](e);
}

ARM void effect_mori2_move(Entity *e) {
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
