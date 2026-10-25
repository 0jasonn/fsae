#include "engine/functions.h"
#include "global.h"
#include "enemy/em20.h"

// Functions in this file: em20_setdir (0x0203e950).

ARM void em20_setdir(Entity *e) {
    if (dushInitCheck(e) != 0) {
        e->action = 3;
        e->timer = 0x1e;
        return;
    }
    e->action = 1;
    e->timer = (Random() & 0xf) + 0xf;
}
