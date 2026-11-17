#include "engine/functions.h"
#include "actor/object/set01.h"

void set01_spawnRandom(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 0x80) {
        if (e->timer < 4) {
            u8 randomIndex = Random() & 0x1f;
            u8 slot = data_020f26dc[data_020d410c[e->type]][data_0212c81c[e->timer]][randomIndex];
            if (slot != 0xff && e->type2 == 0) {
                Entity *child = GetSetWork(0, slot, 1);
                if (child != NULL) {
                    ObjPosCopy(e, child);
                }
            }
        }
        PutObjWork(e);
    }
}
