#include "engine/functions.h"
#include "global.h"
#include "game/shikake.h"

// Switch-block helpers (module shikake), second unit. Original names from the debug build.
//   shikake_playercheck

// Returns 0 as soon as one of the four attached objects of kind 1 fails func_020860dc; 1 otherwise.
ARM BOOL shikake_playercheck(SHIKAKEWORK *req) {
    u8 i;
    Entity *obj;

    for (i = 0; i < 4; i++) {
        obj = req->objs[i];
        if (obj != NULL && obj->objKind == 1) {
            if (func_020860dc(obj) == 0) {
                return 0;
            }
        }
    }
    return 1;
}
