#include "engine/functions.h"
#include "object/set01.h"
#include "global.h"

// Set01 actor, second unit (module set01). Address -> name:
//   0x02058f18 set01_boss (original name)

extern const s8 data_021154f4[]; // (dx, dy) pairs, indexed by subtimer, moved to the child each frame

ARM void set01_boss(Entity *e) {
    Entity *child;

    if (e->timer == 0) {
        child = GetSetWork(0xf, 1, 0x20);
        if (child == NULL) {
            return;
        }
        e->timer = 10;
        e->subtimer--;
        if (e->subtimer == 0) {
            e->action = 3;
            e->timer = 2;
            SoundReq(0x10);
            PutObjWork(e->child);
        }
        ObjPosCopyOfs32(e, child, data_021154f4[e->subtimer * 2] << 16, data_021154f4[e->subtimer * 2 + 1] << 16);
    } else {
        e->timer--;
    }
}
