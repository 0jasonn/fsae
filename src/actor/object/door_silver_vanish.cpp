#include "engine/functions.h"
#include "engine/misc.h"

extern const u8 data_02115be2[]; // (x, y) pairs indexed by type2

// door_silver_vanish, 0x02069378. Fades the display for the 16 frames of the timer; when it ends the door hides, moves
// to the position given by type2 and the effect state is set to 4.
void door_silver_vanish(Entity *e) {
    displayState.reg68 = e->timer | ((0x10 - e->timer) << 8);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action++;
    *(u32 *)&e->spriteSettings &= ~0xc00;
    e->spriteSettings.b0 = 0;
    e->x.HALF.HI = data_02115be2[e->type2 * 2];
    e->y.HALF.HI = data_02115be2[e->type2 * 2 + 1];
    effectState[8] = 4;
}

