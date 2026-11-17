#include "engine/functions.h"
#include "global.h"
#include "actor/object/set43.h"
#include "actor/object/set43_actions.h"

// set43_kasoku (0x0206ca4c): after the wait counter ran out it steps the animation up every 16 frames until
// subtimer reaches the limit, then switches to action 3.
void set43_kasoku(Entity *e) {
    u8 current;

    if (VARS(Vars_Set43, e)->waitCounter != 0) {
        VARS(Vars_Set43, e)->waitCounter--;
        return;
    }
    e->timer--;
    if (e->timer == 0) {
        current = e->subtimer;
        e->timer = 0x10;
        if (current >= VARS(Vars_Set43, e)->limit) {
            e->action = 3;
            e->subtimer = VARS(Vars_Set43, e)->limit;
        } else {
            e->subtimer++;
            InitAnimationForceUpdate(e, (e->type << 2) + e->subtimer);
        }
    }
    UpdateAnimationSingleFrame(e);
}
