#include "engine/functions.h"
#include "object/set1a.h"
#include "global.h"

// Parasw actor (module parasw). Address -> name:
//   0x02059258 parasw_00 (original name)
//   0x02059274 ps00_init (original name)

ARM void parasw_00(Entity *e) {
    parasw00_actions[e->action](e);
}

ARM void ps00_init(Entity *e) {
    e->timer = 0x14;
    e->subtimer = 3;
    e->action++;
}
