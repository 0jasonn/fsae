#include "engine/functions.h"
#include "global.h"
#include "enemy/effectset.h"

// Functions in this file: effectset (0x0203e7a0).

ARM void effectset(Entity *e) {
    Entity *effect = GetSetWork(0xf, data_020d2980[e->type], 0);
    if (effect != 0) {
        ObjPosCopy(e, effect);
    }
}
