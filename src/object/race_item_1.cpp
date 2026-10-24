#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Race item actor, per-type dispatch (module race_item). Address -> name:
//   0x02067b44 race_item_dispatch (per-type handler table data_02115b38 indexed by e->type)
//   (race_item at 0x02067b60 is parked in scratch/agentC/nonmatching)

extern EntityFunc data_02115b38[]; // handler per item type

ARM void race_item_dispatch(Entity *e) {
    data_02115b38[e->type](e);
}
