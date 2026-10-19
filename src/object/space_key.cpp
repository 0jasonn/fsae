#include "engine/functions.h"
#include "object/idoyukaSp.h"
#include "global.h"

// Space key actor (module space_key). Address -> name:
//   0x02059e7c space_key (original name)

ARM void space_key(Entity *e) {
    Entity *child;

    if ((((u8 *)&data_0212c7c8)[0x4c] & (1 << (e->areaIndex - 1))) != 0) {
        child = GetSetWork(0, 5, 0);
        if (child != NULL) {
            child->areaIndex = e->areaIndex;
            child->layer = e->layer;
            child->x.HALF.HI = e->x.HALF.HI;
            child->y.HALF.HI = e->y.HALF.HI;
        }
    }
    PutObjWork(e);
}
