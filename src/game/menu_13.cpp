#include "engine/functions.h"
#include "global.h"
#include "game/menu.h"

// Calls the virtual check (slot 0) of the object with the id.
ARM s32 func_020c2c34(MenuChecker *obj, s32 id) {
    return obj->Check(id);
}
