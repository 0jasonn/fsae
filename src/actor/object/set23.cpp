#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set23.h"

// Set23 actor (module set23). Address -> name:
//   0x02066190 Set23 (dispatcher)

// Dispatcher: runs the handler for the current action.
void Set23(Entity *e) {
    set23_stateTable[e->action](e);
}
