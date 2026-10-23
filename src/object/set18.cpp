#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/set18.h"


// Set18 actor (module set18). Address -> name:
//   0x02065634 Set18 (dispatcher, was Set18)

// Dispatcher: runs the handler for the current action.
ARM void Set18(Entity *e) {
    set18_stateTable[e->action](e);
}
