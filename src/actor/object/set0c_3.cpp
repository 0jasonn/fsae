#include "engine/functions.h"
#include "actor/object/set0c.h"
#include "global.h"

// Set0c actor (module set0c). Address -> name:
//   0x020580a4 set0c_appear, 0x0205811c set0c_vanish (original names)

void set0c_appear(Entity *e) {
    switch (e->type2) {
    case 0:
    case 1:
        RewCell(0x107, VS0C(e)->cell, e->layer);
        AshimotoCheck(e);
        break;
    }
    SoundReq(0x10);
    KemuriSet(e);
    if ((e->type2 & 1) == 0) {
        PutObjWork(e);
    }
    u8 action = e->action;
    e->action = action + 1;
    u8 timer = e->timer;
    VS0C(e)->vanishDelay = timer * 60;
}

void set0c_vanish(Entity *e) {
    u32 mask;
    if (e->type2 != 1) {
        return;
    }
    if (func_02083c84(e) == 0x108) {
        PutObjWork(e);
        return;
    }
    mask = em12_typeMasks[e->areaIndex];
    if ((VS0C(e)->typeBits & mask) == VS0C(e)->typeBits) {
        return;
    }
    if (VS0C(e)->vanishDelay != 0) {
        VS0C(e)->vanishDelay--;
        return;
    }
    e->action = 1;
    RewCellBack(VS0C(e)->cell, e->layer);
    KemuriSet(e);
}
