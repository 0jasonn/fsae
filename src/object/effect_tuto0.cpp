#include "engine/functions.h"
#include "global.h"
#include "object/effect_tuto0.h"

// effect_tuto0 family (module effect_tuto0), 0x0206da58 .. 0x0206db30.
// Address -> name: 0x0206da58 effect_tuto0, 0x0206da74 effect_tuto0_init, 0x0206dadc effect_tuto0_move

ARM void effect_tuto0(Entity *e) {
    effectTuto0Table[e->action](e);
}
