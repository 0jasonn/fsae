#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em24_2.h"

// Functions in this file: Em24 (0x0203fe40), em24_normal (0x0203fe60).

void Em24(Entity *e) {
    EnemyFunctionHandler(e, em24_initStateTable);
    swordset(e);
}

void em24_normal(Entity *e) {
    em24_actionTable[e->action](e);
}
