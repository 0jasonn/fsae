#include "engine/functions.h"
#include "global.h"
#include "object/set41.h"

// Set41 family (module set41), 0x0206c4c0 .. 0x0206c594.
// Address -> name: 0x0206c4c0 appear, 0x0206c4e0 set41_wait, 0x0206c558 set41_appear

ARM void appear(Entity *e) {
    u8 next;
    next = e->action + 1;
    e->timer = 0x14;
    e->action = next;
    KemuriSet(e);
}

ARM void set41_wait(Entity *e) {
    Vars_Set41 *v = VARS(Vars_Set41, e);
    u8 i;

    if (e->type == 1) {
        for (i = 0; i < 4; i++) {
            if (data_0212c7c8[0x5c + i] != 0) {
                appear(e);
                return;
            }
        }
    } else if (e->type == 2) {
        if (v->typeBits == (v->typeBits & em12_typeMasks[e->areaIndex])) {
            appear(e);
        }
    }
}

ARM void set41_appear(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action++;
    e->spriteSettings.b0 = 1;
    func_02085fac(e);
}
