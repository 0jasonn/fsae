#include "engine/functions.h"
#include "global.h"
#include "actor/object/set36.h"
#include "actor/object/set36_actions.h"

extern void setrupee(Entity *e); // 0x0206b4dc (setrupee.cpp)

// set36_fever (0x0206b460): drops a rupee every 8 frames while the timer runs, then repeats the blink count.
void set36_fever(Entity *e) {
    Vars_Set36 *v = VARS(Vars_Set36, e);

    if (v->timer != 0) {
        v->timer--;
        if ((v->timer & 7) == 0) {
            setrupee(e);
        }
        UpdateAnimationSingleFrame(e);
        return;
    }
    if (v->unk_78 != 0) {
        v->unk_78--;
        v->timer = 0x20;
        return;
    }
    // The ROM carries this second test of the same count (it can never be true after the first).
    if (v->unk_78 != 0) {
        v->unk_78 = 4;
        v->timer = 0x20;
        return;
    }
    e->action = 1;
    InitAnimationForceUpdate(e, e->type);
}
