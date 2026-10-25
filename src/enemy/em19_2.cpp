#include "engine/functions.h"
#include "global.h"
#include "enemy/em19.h"
#include "enemy/waitset.h"

// Functions in this file: em19_sitdown (0x0203e4c0).

ARM void em19_sitdown(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        waitset(e);
    }
}
