#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_omoideon family (module effect_omoideon), 0x0206e87c .. 0x0206e93c.
// Address -> name: 0x0206e87c effect_omoideon, 0x0206e898 effect_omoideon_init, 0x0206e8e4 effect_omoideon_move

// Action table of effect_omoideon, effectOmoideonTable
extern const EntityFunc effectOmoideonTable[];

ARM void effect_omoideon(Entity *e) {
    effectOmoideonTable[e->action](e);
}

ARM void effect_omoideon_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->x.HALF.HI = 0x78;
    e->y.HALF.HI = 0x58;
    InitAnimationForceUpdate(e, e->type);
}

ARM void effect_omoideon_move(Entity *e) {
    e->unk_1b = 0xb0;
    e->spriteSettings.b20 = 6;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
    if (e->unk_21 != 0x60) {
        return;
    }
    PutObjWork(e);
}
