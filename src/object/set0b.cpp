#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Set actor unit 8 (module set). Address -> name (original name):
//   0x02057f40 set0b_move

extern u16 frameCounter; // frame counter

ARM void set0b_move(Entity *e) {
    if ((frameCounter & 1) != 0) {
        e->z.HALF.HI--;
    }
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->timer = 0x3c;
    e->x.HALF.HI = e->contactedEntity->x.HALF.HI;
    e->y.HALF.HI = e->contactedEntity->y.HALF.HI + 1;
    e->z.HALF.HI = 0x3c - 0x4f;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b30 = 1;
    set0b_itemAdd(e);
    e->action++;
}
