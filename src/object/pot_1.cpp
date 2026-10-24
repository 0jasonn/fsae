#include "engine/functions.h"
#include "global.h"

// Pot actor, dispatcher (module pot). Address -> name:
//   0x0205e9c0 Pot (state table pot_states, indexed by e->action)
//   (pot_init at 0x0205e9dc is in the next unit)

extern const EntityFunc pot_states[]; // state table indexed by e->action

ARM void Pot(Entity *e) {
    pot_states[e->action](e);
}
