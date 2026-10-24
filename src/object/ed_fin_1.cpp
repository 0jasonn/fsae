#include "engine/functions.h"
#include "global.h"

// Ending fin actor, dispatcher (module ed_fin). Address -> name:
//   0x0205f84c ed_fin (original name, state table ed_fin_states indexed by e->action)
//   (fin_init at 0x0205f868 is in the next unit)

extern const EntityFunc ed_fin_states[]; // state table indexed by e->action

ARM void ed_fin(Entity *e) {
    ed_fin_states[e->action](e);
}
