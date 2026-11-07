#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set22.h"

// Set22 actor, second unit (module set22). Address -> name:
//   0x02065f5c set22_move

// Counts the frame timer down and reads the next script command when it reaches 0.
void set22_move(Entity *e) {
    if (--VARS(Vars_Set22, e)->frameTimer != 0) {
        return;
    }
    VARS(Vars_Set22, e)->frameTimer = e->timer;
    VARS(Vars_Set22, e)->scriptPtr = setinfo(e, VARS(Vars_Set22, e)->scriptPtr);
}

// Waits for the type bits to show up in the area mask, then advances. Without type bits it counts the wait timer
// down and advances when no entity is found at the cell.
void set22_wait(Entity *e) {
    if (VARS(Vars_Set22, e)->typeBits != 0) {
        if (VARS(Vars_Set22, e)->typeBits != (VARS(Vars_Set22, e)->typeBits & em12_typeMasks[e->areaIndex])) {
            return;
        }
        VARS(Vars_Set22, e)->typeBits = 0;
        e->action--;
        VARS(Vars_Set22, e)->frameTimer = e->timer;
        return;
    }
    if (VARS(Vars_Set22, e)->waitTimer != 0) {
        VARS(Vars_Set22, e)->waitTimer--;
        return;
    }
    if (FindTargetInRange(e, VARS(Vars_Set22, e)->cellX, VARS(Vars_Set22, e)->cellY) != 0) {
        e->action--;
        VARS(Vars_Set22, e)->frameTimer = e->timer;
    }
}
