#include "engine/functions.h"
#include "actor/enemy/em26.h"

// em27_init (0x02040e44): initialises the bubble actor (em27).
void em27_init(Entity *e) {
    e->action = 1;
    e->unk_2e = 3;
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b4 = 1;
    e->z.HALF.HI = -2;
    e->hitbox = data_020d3224;
    V(e)->lifeTimer = 0x12c;
    InitAnimationForceUpdate(e, 1);
}
