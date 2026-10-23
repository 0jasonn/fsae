#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_syurenjyo_move, second unit of the effect_syurenjyo module, 0x0206e454 .. 0x0206e4d8.
// Address -> name: 0x0206e454 effect_syurenjyo_move

ARM void effect_syurenjyo_move(Entity *e) {
    e->unk_1b = 0xb1;
    e->spriteSettings.b20 = 8;
    e->spriteSettings.b16 = e->spriteSettings.b20;
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
    e->unk_1b = 0x6a;
}
