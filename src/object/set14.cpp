#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set14 actor (module set14). Address -> name:
//   0x02064880 Set14, 0x0206489c set14_init (original names)

extern const EntityFunc set14_stateTable[]; // indexed by e->action (was set14_stateTable)

ARM void Set14(Entity *e) {
    set14_stateTable[e->action](e);
}
