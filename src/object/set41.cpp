#include "engine/functions.h"
#include "global.h"
#include "object/set41.h"

// Set41 family (module set41), 0x0206c398 .. 0x0206c3b4. set41_init (0x0206c3b4) is parked in scratch/agentA/nonmatching.

ARM void Set41(Entity *e) {
    set41Table[e->action](e);
}
