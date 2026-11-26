#include "engine/functions.h"
#include "actor/enemy/em2c.h"
#include "global.h"
#include "actor/enemy/em2c.h"

// em2c_type1_init_033744 (type1_init, 0x02033744): starts a lever part: action 1, timer 0x20, speed 0x80, moved to its
// rest x for its side, facing away from that side; clears the side's lever timer and plays animation side + 1.
// The statement order (direction before x) is the one that reproduces the ROM's register use and store schedule.
void em2c_type1_init_033744(Entity *e) {
    e->action = 1;
    e->timer = 0x20;
    e->spriteSettings.b0 = 1;
    e->speed = 0x80;
    e->direction = ((V(e)->side ^ 1) << 4) + 8;
    e->x.HALF.HI = e->x.HALF.HI + em2c_restXOffsets[V(e)->side];
    e->unk_1a = 1;
    e->hitbox = data_020d0ef2;
    e->unk_5e.b0 = 0;
    if (em2c_leverTimers[V(e)->side] != 0) {
        em2c_leverTimers[V(e)->side] = 0;
    }
    InitAnimationForceUpdate(e, (u8)(V(e)->side + 1));
}
