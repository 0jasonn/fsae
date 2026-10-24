#include "engine/functions.h"
#include "global.h"

// Grass throw actor, dispatcher (module grass). Address -> name:
//   0x0205ed90 grass_throw (original name, state table grass_throw_states indexed by e->subAction)
//   (grass_throw_init at 0x0205edac is in the next unit)

extern const EntityFunc grass_throw_states[]; // state table indexed by e->subAction

ARM void grass_throw(Entity *e) {
    grass_throw_states[e->subAction](e);
}
