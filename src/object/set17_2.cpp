#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"
#include "object/g_callees.h"

// Set17 actor (module set17). Address -> name:
//   0x02065548 set17_move (original name)

extern const EntityFunc set17_stateTable[]; // indexed by e->action (was set17_stateTable)
extern const u8 set17_hitbox[];             // was set17_hitbox

ARM void set17_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0) {
        return;
    }
    if (e->frame & 0x80) {
        func_020841b0(e);
        PutObjWork(e);
        return;
    }
    TaimatuIgnition(e, 5);
}
