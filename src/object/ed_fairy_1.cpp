#include "engine/functions.h"
#include "global.h"

// Ending fairy actor, dispatcher (module ed_fairy). Address -> name:
//   0x0205f78c ed_fairy (original name, state table ed_fairy_states indexed by e->action)
//   (ed_fairy_init at 0x0205f7a8 is parked in scratch/agentC/nonmatching)
//   (ed_fairy_NoOp at 0x0205f848 is in the next unit)

extern const EntityFunc ed_fairy_states[]; // state table indexed by e->action

ARM void ed_fairy(Entity *e) {
    ed_fairy_states[e->action](e);
}
