#include "engine/functions.h"
#include "global.h"

// Warp hole actor (module warphole). Address -> name:
//   0x0205de34 warphole (original name), 0x0205de50 warphole_init
//   (warphole_init at 0x0205de50 is in scratch/agentF/nonmatching)

extern const EntityFunc data_020d8cb0[]; // state table indexed by e->action


ARM void warphole(Entity *e) {
    data_020d8cb0[e->action](e);
}
