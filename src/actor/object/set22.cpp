#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/set22.h"

// Set22 actor (module set22). Address -> name:
//   0x02065e94 Set22 (dispatcher)

// Dispatcher: runs the handler for the current action.
void Set22(Entity *e) {
    set22_stateTable[e->action](e);
}
