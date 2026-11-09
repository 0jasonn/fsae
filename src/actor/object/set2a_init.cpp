#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x0205a508 set2a_init (original name)

void set2a_init(Entity *e) {
    e->action++;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    if (e->type == 1) {
        e->y.HALF.HI -= 8;
        e->timer = 0x28;
    }
    InitAnimationForceUpdate(e, 0);
    EnqueueSFX(0x2a);
}
