#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   GetFacingDirection

// Direction from e towards target (tail call to the shared direction helper)
ARM u8 GetFacingDirection(Entity *e, Entity *target) {
    return func_02086078(e, target);
}
