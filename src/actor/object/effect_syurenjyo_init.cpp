#include "engine/functions.h"
#include "actor/object/effect_init.h"
#include "actor/object/effectdecls.h"

// 0x0206e3ec (original name). Initialises the syurenjyo (multi-sword) effect.
void effect_syurenjyo_init(Entity *e) {
    u8 action = e->action;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0x78;
    e->subtimer = 8;
    if (e->type == 0xa) {
        e->spriteSettings.b30 = 2;
    }
    set_pos(e);
    InitAnimationForceUpdate(e, e->type);
}
