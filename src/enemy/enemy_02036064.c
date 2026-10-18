#include "enemy/enemy_020347dc.h"
#include "global.h"

ARM void func_02036064(Entity *e) {
    e->direction++;
    e->x.HALF.HI = e->parent->x.HALF.HI + ((V(e)->unk_7c * data_020d7e58[e->direction]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - ((V(e)->unk_7c * data_020d7e58[e->direction + 0x40]) >> 8);
}

ARM void func_020360c0(Entity *e) {
    e->direction++;
    int anim = ((e->direction + 0x10) >> 5) & 7;
    if (e->animationState != anim) {
        e->animationState = anim;
        InitAnimationForceUpdate(e, anim + 0x14);
    }
    e->x.HALF.HI = e->parent->x.HALF.HI + ((V(e)->unk_7c * data_020d7e58[e->direction]) >> 8);
    e->y.HALF.HI = e->parent->y.HALF.HI - ((V(e)->unk_7c * data_020d7e58[e->direction + 0x40]) >> 8);
}

ARM void func_0203614c(Entity *e) {
    if (e->type >= 2) {
        return;
    }
    const u8 *table;
    u8 i;
    u8 k;
    u8 dir;
    dir = (GetFacingDirection(e->parent, e) - 3) & 0x1f;
    k = Random() & 3;
    table = &data_020d11d0[Random() & 0xc];
    for (i = 0; i < 4; i++) {
        Entity *item = CreateFx(0, table[k], 1);
        if (item != NULL) {
            item->direction = dir | 0x80;
            CopyPosition(e, item);
        }
        dir = (dir + 2) & 0x1f;
        k = (k + 1) & 3;
    }
}
