#include "engine/functions.h"
#include "global.h"
#include "enemy/em18_units.h"
// Actor em18 (module em18), unit 6. Address -> name:
//   0x0203df14 em18_init, 0x0203df5c em18_move

// Init: sprite bit b0, no animation offset, the em18 hitbox, action 1, a new direction and animation 0.
ARM void em18_init(Entity *e) {
    e->spriteSettings.b0 = 1;
    e->unk_2e = 0;
    e->hitbox = em06_hitbox;
    e->action = 1;
    getdir(e);
    InitAnimationForceUpdate(e, 0);
}

// Move: when the frame has bit 0x80 set, a new direction and animation 0 are chosen, otherwise the normal move step
// runs. The height follows the animation frame.
ARM void em18_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) != 0) {
        getdir(e);
        InitAnimationForceUpdate(e, 0);
    } else {
        func_020847f8(e);
    }
    e->z.HALF.HI = em18_heightTable[e->frame];
}
