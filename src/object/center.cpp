#include "engine/functions.h"
#include "object/setcommon.h"
#include "global.h"

// Center actor. Address -> name:
//   0x02058c04 center (original name)

ARM void center(Entity *e) {
    e->action = 1;
    e->x.HALF.HI = 0x98;
    if (em12_typeMasks[0] != 0) {
        if (e->y.HALF.HI > 0x68) {
            e->y.HALF.HI--;
        }
    } else {
        e->y.HALF.HI = data_0212ceb0[0].entity->y.HALF.HI;
    }
}
