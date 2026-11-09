#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x0205a480 connect_btn (original name): connection button sprite at (0xe4, 0x58)

void connect_btn(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->unk_1b = 0x6b;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b6 = 3;
        e->unk_20 = 0x80;
        e->spriteSettings.b16 = 0xf;
        e->x.HALF.HI = 0xe4;
        e->y.HALF.HI = 0x58;
        InitAnimationForceUpdate(e, 0);
    } else {
        UpdateAnimationSingleFrame(e);
    }
}
