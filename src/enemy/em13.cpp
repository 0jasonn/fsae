#include "engine/functions.h"
#include "enemy/em13.h"
#include "global.h"

// Renames (renames.txt): em13_damage -> em13_damage

ARM void Em13(Entity *e) {
    if (V(e)->entryFlag == 1) {
        e->unk_6b = 0;
    }
    EnemyFunctionHandler(e, em13_stateTable);
}

ARM void em13_normal(Entity *e) {
    em13_actionTable[e->action](e);
}

ARM void em13_damage(Entity *e) {
    GenericKnockback(e, em13_stateTable);
}

ARM void em13_stop(Entity *e) {
    func_02084f54(e);
    if (e->unk_43 == 0) {
        e->z.HALF.HI = -2;
    }
}
