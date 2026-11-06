#include "engine/functions.h"
#include "engine/misc.h"
#include "global.h"

// Sets the sub-action when the player-state flag at frameCounter+0x12 is set or the player's flag is clear (guess).
void ObjHippariCheck(Entity *e) {
    if (frameCounter[0x12] != 0) {
        e->subAction = 6;
    }
    if (playerWork[e->type2].specialState == 0) {
        e->subAction = 6;
    }
}
