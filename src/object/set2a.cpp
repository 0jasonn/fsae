#include "engine/functions.h"
#include "global.h"

// Set2a actor (module set2a). Address -> name:
//   0x0205a4ec Set2a (original name), dispatches through set2a_actions
//   0x0205a508 set2a_init is in scratch/agentF/nonmatching/set2a_init.c

extern const EntityFunc set2a_actions[]; // set2a_actions, indexed by e->action

ARM void Set2a(Entity *e) {
    set2a_actions[e->action](e);
}
