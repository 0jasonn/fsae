#include "Unknown/Enemy_020347dc.h"
#include "global.h"

ARM void func_02036064(Entity *e) {
    e->unk_2b++;
    e->unk_30.HALF.HI = e->unk_54->unk_30.HALF.HI + ((V(e)->unk_7c * data_020d7e58[e->unk_2b]) >> 8);
    e->unk_34.HALF.HI = e->unk_54->unk_34.HALF.HI - ((V(e)->unk_7c * data_020d7e58[e->unk_2b + 0x40]) >> 8);
}

ARM void func_020360c0(Entity *e) {
    e->unk_2b++;
    int anim = ((e->unk_2b + 0x10) >> 5) & 7;
    if (e->unk_2a != anim) {
        e->unk_2a = anim;
        func_020859e0(e, anim + 0x14);
    }
    e->unk_30.HALF.HI = e->unk_54->unk_30.HALF.HI + ((V(e)->unk_7c * data_020d7e58[e->unk_2b]) >> 8);
    e->unk_34.HALF.HI = e->unk_54->unk_34.HALF.HI - ((V(e)->unk_7c * data_020d7e58[e->unk_2b + 0x40]) >> 8);
}

ARM void func_0203614c(Entity *e) {
    if (e->unk_0a >= 2) {
        return;
    }
    const u8 *table;
    u8 i;
    u8 k;
    u8 dir;
    dir = (func_0204fdf0(e->unk_54, e) - 3) & 0x1f;
    k = func_0208455c() & 3;
    table = &data_020d11d0[func_0208455c() & 0xc];
    for (i = 0; i < 4; i++) {
        Entity *item = func_02076858(0, table[k], 1);
        if (item != NULL) {
            item->unk_2b = dir | 0x80;
            func_0205031c(e, item);
        }
        dir = (dir + 2) & 0x1f;
        k = (k + 1) & 3;
    }
}
