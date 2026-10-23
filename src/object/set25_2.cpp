#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set25.h"

// Set25 actor, second unit (module set25). Address -> name:
//   0x02066630 set25_move

// Counts the four contact timers and the subtimer down. When the contacted entity touches this one, the timer of its type
// is checked and vitaldec is called when it has run out.
ARM void set25_move(Entity *e) {
    if (VARS(Vars_Set25, e)->timers[0] != 0) {
        VARS(Vars_Set25, e)->timers[0]--;
    }
    if (VARS(Vars_Set25, e)->timers[1] != 0) {
        VARS(Vars_Set25, e)->timers[1]--;
    }
    if (VARS(Vars_Set25, e)->timers[2] != 0) {
        VARS(Vars_Set25, e)->timers[2]--;
    }
    if (VARS(Vars_Set25, e)->timers[3] != 0) {
        VARS(Vars_Set25, e)->timers[3]--;
    }
    if (e->subtimer != 0) {
        e->subtimer--;
    }
    if ((e->contactFlags & 0x80) == 0) {
        return;
    }
    switch (e->contactedEntity->type) {
    case 0:
        if (VARS(Vars_Set25, e)->timers[0] != 0) {
            return;
        }
        vitaldec(e, &VARS(Vars_Set25, e)->timers[0]);
        return;
    case 1:
        if (VARS(Vars_Set25, e)->timers[1] != 0) {
            return;
        }
        vitaldec(e, &VARS(Vars_Set25, e)->timers[1]);
        return;
    case 2:
        if (VARS(Vars_Set25, e)->timers[2] != 0) {
            return;
        }
        vitaldec(e, &VARS(Vars_Set25, e)->timers[2]);
        return;
    case 3:
        if (VARS(Vars_Set25, e)->timers[3] != 0) {
            return;
        }
        vitaldec(e, &VARS(Vars_Set25, e)->timers[3]);
        return;
    default:
        if (e->subtimer != 0) {
            return;
        }
        vitaldec(e, &e->subtimer);
        return;
    }
}
