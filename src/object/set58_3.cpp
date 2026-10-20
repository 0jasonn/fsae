#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set58.h"

// Set58 hane actions (module set58). Address -> name:
//   0x02073780 set58_hane (original name; dispatches on e->action)
//   0x0207379c hane_init is in scratch/agentD/nonmatching (near miss)

extern const EntityFunc set58_haneActions[]; // set58_haneActions, indexed by e->action

ARM void set58_hane(Entity *e) {
    set58_haneActions[e->action](e);
}
