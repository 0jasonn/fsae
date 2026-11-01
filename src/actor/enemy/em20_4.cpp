#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em20.h"
#include "actor/enemy/kamen.h"

// Functions in this file: em20_dushInit (0x0203e990).

void em20_dushInit(Entity *e) {
    UpdateAnimationSingleFrame(e);
    UpdateAnimationSingleFrame(e);
    if (--e->timer == 0) {
        e->action = 4;
        e->speed = 0x300;
        return;
    }
    kamen_kemuriSet(e);
}
