#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Shutter actor (module ss). Address -> name:
//   0x02067bdc shutter_set (original name, state table data_02115b1c indexed by e->action)
//   (ss_init at 0x02067bf8 is parked in scratch/agentC/nonmatching)

extern EntityFunc data_02115b1c[]; // state table indexed by e->action

ARM void shutter_set(Entity *e) {
    data_02115b1c[e->action](e);
}
