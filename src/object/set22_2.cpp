#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set22.h"

// Set22 actor, second unit (module set22). Address -> name:
//   0x02065f5c set22_move

// Counts the frame timer down and reads the next script command when it reaches 0.
ARM void set22_move(Entity *e) {
    if (--VARS(Vars_Set22, e)->frameTimer != 0) {
        return;
    }
    VARS(Vars_Set22, e)->frameTimer = e->timer;
    VARS(Vars_Set22, e)->scriptPtr = setinfo(e, VARS(Vars_Set22, e)->scriptPtr);
}
