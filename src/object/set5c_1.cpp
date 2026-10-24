#include "engine/functions.h"
#include "global.h"

// Set5c actor, dispatcher (module set5c). Address -> name:
//   0x0205f9b8 Set5c (state table set5c_states, indexed by e->action)
//   (set5c_init at 0x0205f9d4 is in the next unit)

extern const EntityFunc set5c_states[]; // state table indexed by e->action

ARM void Set5c(Entity *e) {
    set5c_states[e->action](e);
}
