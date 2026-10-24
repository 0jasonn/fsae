#include "engine/functions.h"
#include "global.h"

// Set5e actor, dispatcher (module set5e). Address -> name:
//   0x0205ffd4 Set5e (state table set5e_states, indexed by e->action)
//   (set5e_init at 0x0205fff0 is parked in scratch/agentC/nonmatching; set5e_move is in src/object/set5e_2.cpp)

extern const EntityFunc set5e_states[]; // state table indexed by e->action

ARM void Set5e(Entity *e) {
    set5e_states[e->action](e);
}
