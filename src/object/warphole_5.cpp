#include "engine/functions.h"
#include "global.h"
#include "object/protos.h"

// Warp hole actor, third unit (module warphole). Address -> name:
//   0x0205e078 warphole_wait2 (original name)
//   (pos_copy at 0x0205e05c is in warphole_2.cpp; warphole_exit at 0x0205e114 is in warphole_3.cpp)

ARM void warphole_wait2(Entity *e) {
    u8 flag;
    Entity *target;

    if (data_0212c7c8[0x6e] >= 3 && data_0212c7c8[0x4f] == e->type2) {
        flag = 0;
        e->action = e->action + 1;
        e->spriteSettings.b16 = 1;
        InitAnimationForceUpdate(e, flag);
        if ((func_02084110(e) & 1) == 0) {
            flag = 1;
        }
        target = GetSetWork(0x42, flag, 0);
        if (target != NULL) {
            ObjPosCopy(e, target);
        }
    } else {
        UpdateAnimationSingleFrame(e);
    }
    warphole_exit(e);
}
