#include "engine/functions.h"
#include "actor/object/moji.h"

// 0x02070140 (original name). Places the moji actor using the per-type position table.
void moji_init(Entity *e) {
    const u8 *posTable;

    e->action = 1;
    e->spriteSettings.b0 = 2;
    posTable = moji_posTables[e->type - 1];
    e->x.HALF.HI = posTable[e->type2];
    e->y.HALF.HI = 0x28;
    e->z.HALF.HI = 0x28 - 0x68;
    InitAnimationForceUpdate(e, e->type2);
}
