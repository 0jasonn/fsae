#include "engine/functions.h"
#include "enemy/em2d.h"
#include "global.h"

ARM void cercleMove2(Entity *e) {
    e->direction++;
    e->x.HALF.HI = e->parent->x.HALF.HI + ((V(e)->orbitRadius * trigTable[e->direction]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - ((V(e)->orbitRadius * trigTable[e->direction + 0x40]) >> 8);
}

ARM void cercleMoveC2(Entity *e) {
    e->direction++;
    int anim = ((e->direction + 0x10) >> 5) & 7;
    if (e->animationState != anim) {
        e->animationState = anim;
        InitAnimationForceUpdate(e, anim + 0x14);
    }
    e->x.HALF.HI = e->parent->x.HALF.HI + ((V(e)->orbitRadius * trigTable[e->direction]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - ((V(e)->orbitRadius * trigTable[e->direction + 0x40]) >> 8);
}

ARM void testiRupeeSet(Entity *e) {
    if (e->type >= 2) {
        return;
    }
    const u8 *itemIds;
    u8 i;
    u8 itemIndex;
    u8 dropDir;
    dropDir = (GetFacingDirection(e->parent, e) - 3) & 0x1f;
    itemIndex = Random() & 3;
    itemIds = &em2d_rupeeItems[Random() & 0xc];
    for (i = 0; i < 4; i++) {
        Entity *item = GetSetWork(0, itemIds[itemIndex], 1);
        if (item != NULL) {
            item->direction = dropDir | 0x80;
            ObjPosCopy(e, item);
        }
        dropDir = (dropDir + 2) & 0x1f;
        itemIndex = (itemIndex + 1) & 3;
    }
}
