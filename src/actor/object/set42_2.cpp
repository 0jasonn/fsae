#include "engine/functions.h"
#include "global.h"
#include "actor/object/set42.h"

// Set42 family (module set42), from 0x0206c850.
// Address -> name: 0x0206c850 set42_move

void set42_move(Entity *e) {
    if (e->timer == 0) {
        gameState.unk_6e = 4;
    } else {
        e->timer--;
    }
    if (e->type == 0) {
        func_02085934(e, 3);
        return;
    }
    UpdateAnimationSingleFrame(e);
}
