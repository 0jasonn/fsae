#include "engine/functions.h"
#include "global.h"

// Set4b actor (module set4b). Address -> name:
//   0x0205e280 Set4b (provisional name for the dispatcher, renamed from Set4b)
//   (set4b_init at 0x0205e29c is in scratch/agentF/nonmatching)
//   (set4b_move at 0x0205e300 is in the next unit)

extern const EntityFunc data_02115898[]; // state table indexed by e->action

ARM void Set4b(Entity *e) {
    data_02115898[e->action](e);
}
