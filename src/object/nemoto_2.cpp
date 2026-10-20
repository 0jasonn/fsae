#include "engine/functions.h"
#include "global.h"
#include "object/set40.h"

// nemoto family (module nemoto), 0x0206c328 .. 0x0206c398.
// Address -> name: 0x0206c328 nemoto_setdist (original setdist). Vars_Set40 holds savedX/savedY/value.

ARM void nemoto_setdist(Entity *e) {
    Vars_Set40 *v = VARS(Vars_Set40, e);

    switch (e->type) {
    case 0:
        v->value = e->y.HALF.HI - v->savedY;
        break;
    case 1:
        v->value = v->savedX - e->x.HALF.HI;
        break;
    case 2:
        v->value = v->savedY - e->y.HALF.HI;
        break;
    case 3:
        v->value = e->x.HALF.HI - v->savedX;
        break;
    }
}
