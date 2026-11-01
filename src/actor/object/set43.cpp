#include "engine/functions.h"
#include "global.h"
#include "actor/object/set43.h"

// Set43 family (module set43), 0x0206c894 .. 0x0206c8b0 (set43_init, 0x0206c8b0, is not attempted yet).
// Address -> name: 0x0206c894 Set43

void Set43(Entity *e) {
    set43Table[e->action](e);
}
