#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// 0x0207ccfc tama0a_type1_init (original type1_init): starts the type 1 ball in action 1 with a default timer of 5.

void tama0a_type1_init(Entity *e) {
    e->action = 1;
    if (e->timer == 0) {
        e->timer = 5;
    }
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020dca70;
    InitAnimationForceUpdate(e, 1);
}
