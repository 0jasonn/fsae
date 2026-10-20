#include "engine/functions.h"
#include "global.h"
#include "object/effect_mori.h"

// effect_mori family (module effect_mori), 0x0206dd84 .. 0x0206ddc8.
// Address -> name: 0x0206dd84 effect_mori_move

ARM void effect_mori_move(Entity *e) {
    u8 timer = e->timer;

    e->timer = timer - 1;
    if (timer == 0) {
        e->timer = (Random() & 0xf) << 3;
        e->action--;
    }
    UpdateAnimationSingleFrame(e);
}
