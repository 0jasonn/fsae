#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set15 actor and its two empty state functions (module set15). Address -> name:
//   0x02064bd0 Set15 (original name), 0x02064bec set15_nop0, 0x02064bf0 set15_nop1

extern const EntityFunc set15_stateTable[]; // indexed by e->action (was set15_stateTable)

ARM void Set15(Entity *e) {
    set15_stateTable[e->action](e);
}

ARM void set15_nop0(Entity *e) {
}

ARM void set15_nop1(Entity *e) {
}
