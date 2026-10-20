#include "engine/functions.h"
#include "global.h"
#include "object/set42.h"

// Set42 family (module set42), from 0x0206c850.
// Address -> name: 0x0206c850 set42_move

ARM void set42_move(Entity *e) {
    if (e->timer == 0) {
        data_0212c7c8[0x6e] = 4;
    } else {
        e->timer--;
    }
    if (e->type == 0) {
        func_02085934(e, 3);
        return;
    }
    UpdateAnimationSingleFrame(e);
}
