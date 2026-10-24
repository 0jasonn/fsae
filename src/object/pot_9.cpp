#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Pot actor, throw end (module pot). Address -> name:
//   0x0205f084 pot_throw_end (original name throw_end): clashes with the player that threw the pot

ARM void pot_throw_end(Entity *e) {
    pot_clash(e, data_0212ceb0[e->type2].entity);
}
