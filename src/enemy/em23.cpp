#include "engine/functions.h"
#include "global.h"
#include "enemy/em23.h"

// Functions in this file: em23_normal (0x0203fac0).

ARM void em23_normal(Entity *e) {
    em23_actionTable[e->action](e);
}
