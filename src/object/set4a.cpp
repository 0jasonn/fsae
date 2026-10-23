#include "engine/functions.h"
#include "global.h"

// Set4a actor (module set4a). Address -> name:
//   0x0205e18c Set4a (original name), 0x0205e1a8 set4a_init
//   (set4a_init at 0x0205e1a8 is in scratch/agentF/nonmatching; set4a_move at 0x0205e204 is in the next unit)

extern const EntityFunc data_020d8d08[]; // state table indexed by e->action

ARM void Set4a(Entity *e) {
    data_020d8d08[e->action](e);
}
