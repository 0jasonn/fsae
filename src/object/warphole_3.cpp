#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/warphole.h"

// Warp hole actor, third unit (module warphole). Address -> name:
//   0x0205e114 warphole_exit (original name)

ARM void warphole_exit(Entity *e) {
    int players = func_02084110(e);

    if (players & 1) {
        pos_copy(e, data_0212ceb0[0].entity);
    }
    if (players & 2) {
        pos_copy(e, data_0212ceb0[1].entity);
    }
    if (players & 4) {
        pos_copy(e, data_0212ceb0[2].entity);
    }
    if (players & 8) {
        pos_copy(e, data_0212ceb0[3].entity);
    }
}
