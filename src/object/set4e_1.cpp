#include "engine/functions.h"
#include "global.h"

// Set4e actor, dispatcher (module set4e). Address -> name:
//   0x0205e620 Set4e (state table set4e_states, indexed by e->action)

extern const EntityFunc set4e_states[]; // state table indexed by e->action

ARM void Set4e(Entity *e) {
    set4e_states[e->action](e);
}
