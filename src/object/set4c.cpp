#include "engine/functions.h"
#include "global.h"

// Set4c actor (module set4c). Address -> name:
//   0x0205e3b8 Set4c (original name)
//   (set4c_init at 0x0205e3d4 is in the next unit)

extern const EntityFunc data_020d8db0[]; // state table indexed by e->action

ARM void Set4c(Entity *e) {
    data_020d8db0[e->action](e);
}
