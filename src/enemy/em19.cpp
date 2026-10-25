#include "engine/functions.h"
#include "global.h"
#include "enemy/em19.h"

// Functions in this file: em19_normal (0x0203e0ac).

ARM void em19_normal(Entity *e) {
    em19_actionTable[e->action](e);
}
