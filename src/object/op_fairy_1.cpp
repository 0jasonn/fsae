#include "engine/functions.h"
#include "global.h"

// Fairy opening actor, dispatchers (module op_fairy). Address -> name:
//   0x0205f448 pot_typeDispatch (table pot_typeHandlers, indexed by e->type; a pot type dispatcher)
//   0x0205f464 op_fairy (state table op_fairy_states, indexed by e->action)
//   (op_fairy_init at 0x0205f480 is in the next unit)

extern const EntityFunc pot_typeHandlers[]; // handler per type
extern const EntityFunc op_fairy_states[]; // state table indexed by e->action

ARM void pot_typeDispatch(Entity *e) {
    pot_typeHandlers[e->type](e);
}

ARM void op_fairy(Entity *e) {
    op_fairy_states[e->action](e);
}
