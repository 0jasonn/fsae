#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set25.h"

// Set25 actor (module set25). Address -> name:
//   0x020665c0 Set25 (dispatcher)

// Dispatcher: runs the handler for the current action.
void Set25(Entity *e) {
    set25_stateTable[e->action](e);
}
