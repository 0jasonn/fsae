#include "engine/functions.h"
#include "actor/object/setcommon.h"

typedef struct Vars_Set0e {
    u8 unk_00[0x60];
    u32 typeBits;
} Vars_Set0e;

void Set0e(Entity *e) {
    Entity *item;

    switch (e->action) {
    case 0:
        e->action++;
        VARS(Vars_Set0e, e)->typeBits = ParseTypeBits(e->type);
        break;
    case 1:
        if ((VARS(Vars_Set0e, e)->typeBits & em12_typeMasks[e->areaIndex]) != VARS(Vars_Set0e, e)->typeBits) {
            break;
        }
        if (e->timer == 0) {
            goto timerDefault;
        }
        if (e->timer == 1) {
            goto timerOne;
        }
    timerDefault:
        KemuriSet(e);
        item = ItemSet(e, e->type2);
        if (item != NULL && e->type2 != 5) {
            item->type2 |= 1;
            item->timer = 8;
        }
        goto timerDone;
    timerOne:
        item = ItemSet(e, e->type2);
        if (item != NULL) {
            item->type2 |= 0x80;
            item->zVelocity = 1;
            if (e->type2 != 5) {
                item->type2 |= 1;
                item->timer = 8;
            }
        }
    timerDone:
        SoundReq(0x10);
        PutObjWork(e);
        break;
    }
}
