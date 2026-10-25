#include "engine/functions.h"
#include "global.h"
#include "enemy/em23_3.h"

// Functions in this file: em23_init (0x0203fb88).

ARM void em23_init(Entity *e) {
    e->action = 1;
    e->subtimer = Random();
    e->spriteSettings.b0 = 1;
    e->hitbox = data_020d2d98;
    e->direction = Random() & 0x1f;
    if (VARS(Vars_em23, e)->respawnDelay != 0) {
        VARS(Vars_em23, e)->respawnDelay = 0x258;
    }
    InitAnimationForceUpdate(e, 0);
}
