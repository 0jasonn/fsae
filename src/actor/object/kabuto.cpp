#include "engine/functions.h"
#include "actor/object/kabuto.h"
#include "global.h"

// Sword module, continued: kabutoEvent (0x0207bc48).


// kabutoEvent (0x0207bc48)
void kabutoEvent(Entity *e) {
    u8 row;
    u8 col;
    s8 dy;
    s8 dx;

    dy = -16;
    for (row = 0; row < 3; row++) {
        dx = -16;
        for (col = 0; col < 3; col++) {
            func_0208a240(e, 0, (u16)(e->x.HALF.HI + dx), (u16)(e->y.HALF.HI + dy));
            dx += 16;
        }
        dy += 16;
    }
}
