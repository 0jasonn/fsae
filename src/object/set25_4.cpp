#include "engine/functions.h"
#include "global.h"
#include "object/set25_3.h"

// Set25 family, fourth unit (module set25). Address -> name:
//   0x02067770 breakSmokeSet (original name breakSmokeSet(OBJ_WORK_*))

// Spawns four smoke pieces (set type 2) around the actor, offset by the table value on x and by 0x14 on y
ARM void breakSmokeSet(Entity *e) {
    Entity *piece;

    piece = GetSetWork(15, 2, 0);
    if (piece != NULL) {
        piece->x.HALF.HI = e->x.HALF.HI - data_020da420[e->timer >> 1];
        piece->y.HALF.HI = e->y.HALF.HI - 0x14;
        piece->layer = e->layer;
    }
    piece = GetSetWork(15, 2, 0);
    if (piece != NULL) {
        piece->x.HALF.HI = e->x.HALF.HI + data_020da420[e->timer >> 1];
        piece->y.HALF.HI = e->y.HALF.HI - 0x14;
        piece->layer = e->layer;
    }
    piece = GetSetWork(15, 2, 0);
    if (piece != NULL) {
        piece->x.HALF.HI = e->x.HALF.HI - data_020da420[e->timer >> 1];
        piece->y.HALF.HI = e->y.HALF.HI + 0x14;
        piece->layer = e->layer;
    }
    piece = GetSetWork(15, 2, 0);
    if (piece != NULL) {
        piece->x.HALF.HI = e->x.HALF.HI + data_020da420[e->timer >> 1];
        piece->y.HALF.HI = e->y.HALF.HI + 0x14;
        piece->layer = e->layer;
    }
}
