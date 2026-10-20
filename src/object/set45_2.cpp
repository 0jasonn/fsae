#include "engine/functions.h"
#include "global.h"
#include "object/set45.h"

// Set45 family (module set45), 0x0206d4d0 .. 0x0206d5c4 (set45_init at 0x0206d418 is parked in scratch/agentA/nonmatching).
// Address -> name: 0x0206d4d0 set45_move, 0x0206d530 set45_jigoshori, 0x0206d584 set45_die

ARM void set45_move(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);
    int cellResult;

    UpdateAnimationSingleFrame(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    cellResult = func_02083ca8(v->cell, e->layer);
    if (cellResult == 0x2f || cellResult == 0x58) {
        e->action = 3;
        e->timer = 0x1e;
        return;
    }
    e->action = 2;
    InitAnimationForceUpdate(e, 4);
}

ARM void set45_jigoshori(Entity *e) {
    Vars_NemotoCell *v = VARS(Vars_NemotoCell, e);

    UpdateAnimationSingleFrame(e);
    if ((e->frame & 0x80) == 0) {
        return;
    }
    if (e->type > 4) {
        e->type = 4;
    }
    RewCell(set45JigoshoriIds[e->type], v->cell, e->layer);
    PutObjWork(e);
}

ARM void set45_die(Entity *e) {
    e->spriteSettings.b0 ^= 1;
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}
