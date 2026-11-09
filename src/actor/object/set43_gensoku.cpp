#include "engine/functions.h"
#include "global.h"
#include "actor/object/set43.h"
#include "actor/object/object_handlers.h"

// 0x0206cb1c set43_gensoku (original name): counts the animation steps down every 16 frames, then returns to action 1.

void set43_gensoku(Entity *e) {
    if (--e->timer == 0) {
        e->timer = 0x10;
        if (0 == e->subtimer) {
            e->action = 1;
            VARS(Vars_Set43, e)->waitCounter = VARS(Vars_Set43, e)->savedCounter;
        } else {
            e->subtimer--;
            InitAnimationForceUpdate(e, (e->type << 2) + e->subtimer);
        }
    }
    UpdateAnimationSingleFrame(e);
}
