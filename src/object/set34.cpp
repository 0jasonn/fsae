#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc set34Table[];        // set34Table, indexed by action

// Set34, 0x0206ab6c: runs the state function for the current action.
ARM void Set34(Entity *e) {
    set34Table[e->action](e);
}
