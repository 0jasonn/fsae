#include "engine/functions.h"
#include "global.h"

// Functions in this file: em23_vanish (0x0203fc98).

ARM void em23_vanish(Entity *e) {
    e->spriteSettings.b0 ^= 1;
    e->timer--;
    if (e->timer == 0) {
        PutObjWork(e);
    }
}
