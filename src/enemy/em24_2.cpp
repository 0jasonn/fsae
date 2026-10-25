#include "engine/functions.h"
#include "global.h"
#include "enemy/em24_2.h"

// Functions in this file: Em24 (0x0203fe40), em24_normal (0x0203fe60).

ARM void Em24(Entity *e) {
    EnemyFunctionHandler(e, em24_initStateTable);
    swordset(e);
}

ARM void em24_normal(Entity *e) {
    em24_actionTable[e->action](e);
}
