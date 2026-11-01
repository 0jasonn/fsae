#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"
#include "actor/object/g_callees.h"
#include "actor/object/set13.h"

// Set13 actor (module set13). Address -> name:
//   0x020644cc Set13 (original name)

void Set13(Entity *e) {
    set13_stateTable[e->action](e);
}
