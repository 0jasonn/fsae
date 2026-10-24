#include "engine/functions.h"
#include "global.h"

// Set4d actor, dispatcher and third unit (module set4d). Address -> name:
//   0x0205e53c Set4d (state table set4d_states, indexed by e->action)
//   (set4d_init at 0x0205e558 is in src/object/set4d.cpp; set4d_move at 0x0205e580 is parked in scratch/agentC/nonmatching)

extern const EntityFunc set4d_states[]; // state table indexed by e->action

ARM void Set4d(Entity *e) {
    set4d_states[e->action](e);
}
