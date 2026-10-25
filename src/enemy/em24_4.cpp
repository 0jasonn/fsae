#include "engine/functions.h"
#include "global.h"
#include "enemy/em24_4.h"

// Functions in this file: fuwafuwa (0x0203fe0c).

ARM void fuwafuwa(Entity *e) {
    s32 phase = (frameCounter + e->subtimer) & 0xf;
    if ((phase & 3) == 0) {
        e->z.HALF.HI = fuwafuwaTable[phase >> 2];
    }
}
