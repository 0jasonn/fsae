#include "engine/functions.h"
#include "global.h"
#include "object/set40.h"

// Set40 family (module set40), 0x0206bce4 .. 0x0206bd70.
// Address -> name: 0x0206bce4 Set40 (set40_init, 0x0206bd70, is parked in scratch/agentA/nonmatching)

ARM void Set40(Entity *e) {
    Vars_Set40 *v = VARS(Vars_Set40, e);

    switch (v->mode) {
    case 0:
        set40Table[e->action](e);
        func_02085d78(e);
        set40Slots[v->slot] = v->value;
        break;
    case 1:
        set40AltTable[e->action](e);
        break;
    case 2:
        if (e->action == 0) {
            nemoto_init(e);
        }
        break;
    }
}
