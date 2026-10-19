#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Set07 actor (module set07). Address -> name:
//   0x02061494 Set07 (original name)

extern const EntityFunc data_020d92a0[]; // indexed by e->action

ARM void Set07(Entity *e) {
    data_020d92a0[e->action](e);
}
