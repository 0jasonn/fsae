#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set33Table[];        // set33Table, indexed by action

// Set33, 0x0206a0c8: runs the state function for the current action.
ARM void Set33(Entity *e) {
    set33Table[e->action](e);
}
