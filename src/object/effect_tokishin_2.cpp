#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_tokishin_move, second unit of the effect_tokishin module, 0x0206e34c .. 0x0206e3d0.
// Address -> name: 0x0206e34c effect_tokishin_move

ARM void effect_tokishin_move(Entity *e) {
    e->unk_1b = 0xb0;
    e->spriteSettings.b20 = 6;
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
