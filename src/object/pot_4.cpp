#include "engine/functions.h"
#include "global.h"

// Pot actor, state reset (module pot). Address -> name:
//   0x0205f0e0 throw_holdoff (original name): sets the state to 1 and clears the sub action
//   (throw_hold at 0x0205f0b4 is in the previous unit; pot_clash at 0x0205f224 is in the next unit)

ARM void throw_holdoff(Entity *e) {
    e->action = 1;
    e->subAction = 0;
}
