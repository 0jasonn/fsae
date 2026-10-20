#include "engine/functions.h"
#include "global.h"
#include "object/set42.h"

// Set42 family (module set42), 0x0206c704 .. 0x0206c720. set42_init and set42_wait are parked in scratch/agentA/nonmatching.

ARM void Set42(Entity *e) {
    set42Table[e->action](e);
}
