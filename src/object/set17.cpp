#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set17 actor (module set17). Address -> name:
//   0x020654c0 set17_run (dispatcher, was set17_run)

extern const EntityFunc set17_stateTable[]; // indexed by e->action (was set17_stateTable)
extern const u8 set17_hitbox[];             // was set17_hitbox

ARM void set17_run(Entity *e) {
    set17_stateTable[e->action](e);
}
