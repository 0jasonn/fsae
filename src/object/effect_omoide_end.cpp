#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_omoide_end family (module effect_omoide_end), 0x0206f0a8 .. 0x0206f174.
// Address -> name: 0x0206f0a8 effect_omoide_end, 0x0206f0c4 effect_omoide_end_init, 0x0206f114 effect_omoide_end_move

// Action table of effect_omoide_end, effectOmoideEndTable
extern const EntityFunc effectOmoideEndTable[];

ARM void effect_omoide_end(Entity *e) {
    effectOmoideEndTable[e->action](e);
}

ARM void effect_omoide_end_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->x.HALF.HI = 0x78;
    e->y.HALF.HI = 0x58;
    e->y.HALF.HI = e->y.HALF.HI + 9;
    InitAnimationForceUpdate(e, e->type);
}

ARM void effect_omoide_end_move(Entity *e) {
    u8 timer;

    e->unk_1b = 0xb0;
    e->spriteSettings.b20 = 6;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
    timer = e->timer;
    e->timer = timer + 1;
    if (timer == 0xf0) {
        PutObjWork(e);
    }
}
