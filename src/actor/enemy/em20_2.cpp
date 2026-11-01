#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em20.h"

// Functions in this file: Em20 (0x0203e7d8), em20_normal (0x0203e810).

void Em20(Entity *e) {
    if (e->type == 0) {
        EnemyFunctionHandler(e, em20_stateTable);
    } else {
        kamen_actionTable[e->action](e);
    }
}

void em20_normal(Entity *e) {
    if (magneCheck(e) != 0) {
        return;
    }
    em20_actionTable[e->action](e);
}
