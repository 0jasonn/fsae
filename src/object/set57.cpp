#include "engine/functions.h"
#include "global.h"
#include "object/objdecls.h"
#include "object/set57.h"

// Set57 actor, second unit (module set57). Address -> name:
//   0x020732f4 set57_move (original name)

ARM void set57_move(Entity *e) {
    if (V57(e)->tileIndex == *V57(e)->cellPtr) {
        UpdateAnimationSingleFrame(e);
        if ((e->frame & 0x80) == 0) {
            return;
        }
        InitAnimationForceUpdate(e, 0);
        e->unk_28 = (Random() & 0xf0) + 1;
        return;
    }
    {
        Entity *item = ItemSet(e, set57_itemIds[e->type]);
        if (item != NULL) {
            item->type2 = 4;
            item->y.HALF.HI += 8;
            item->z.HALF.HI -= 8;
            item->direction = 0x90;
        }
    }
    PutObjWork(e);
}
