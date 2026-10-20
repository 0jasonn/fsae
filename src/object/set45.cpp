#include "engine/functions.h"
#include "global.h"
#include "object/set45.h"

// Set45 family (module set45), 0x0206d3fc .. 0x0206d5c4.
// Address -> name: 0x0206d3fc Set45, 0x0206d418 set45_init, 0x0206d4d0 set45_move,
// 0x0206d530 set45_jigoshori, 0x0206d584 set45_die

ARM void Set45(Entity *e) {
    set45Table[e->action](e);
}
