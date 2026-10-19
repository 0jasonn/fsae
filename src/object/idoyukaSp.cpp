#include "engine/functions.h"
#include "object/idoyukaSp.h"
#include "global.h"

// idoyukaSp actor (module idoyukaSp). Address -> name:
//   0x02059ee8 idoyukaSp (provisional, idoyukaSp_actions[e->action](e))
//   0x02059f04 idoyukaSp_init (original name)
//   0x02059f28 idoyukaSp_wait (original name)
//   0x02059f90 idoyukaSp_wait2 (original name)

ARM void idoyukaSp(Entity *e) {
    idoyukaSp_actions[e->action](e);
}

ARM void idoyukaSp_init(Entity *e) {
    VIDOYUKA(e)->typeBits = ParseTypeBits(e->type2);
    e->action++;
}

ARM void idoyukaSp_wait(Entity *e) {
    Entity *child;

    if ((VIDOYUKA(e)->typeBits & em12_typeMasks[e->areaIndex]) != VIDOYUKA(e)->typeBits) {
        return;
    }
    child = GetObjWork();
    if (child != NULL) {
        if (func_02085024(child, &idoyukaSp_list[e->timer * 4], e->areaIndex)) {
            child->areaIndex = e->areaIndex;
        }
    }
    e->action++;
}

ARM void idoyukaSp_wait2(Entity *e) {
    if (VIDOYUKA(e)->typeBits != (VIDOYUKA(e)->typeBits & em12_typeMasks[e->areaIndex])) {
        e->action--;
    }
}
