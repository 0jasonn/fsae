#include "engine/functions.h"
#include "global.h"
#include "enemy/em18_2.h"

// Functions in this file: em18_normal (0x0203dc68).

ARM void em18_normal(Entity *e) {
    em18_actionTable[e->action](e);
}
