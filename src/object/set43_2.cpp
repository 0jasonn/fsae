#include "engine/functions.h"
#include "global.h"
#include "object/set43.h"

// Set43 family (module set43), 0x0206ca20 .. 0x0206ca4c.
// Address -> name: 0x0206ca20 set43_wait

ARM void set43_wait(Entity *e) {
    if (switchcheck(e) != 0) {
        e->action = 2;
        if (VARS(Vars_Set43, e)->flag != 0) {
            e->linkedEntity = NULL;
        }
    }
}
