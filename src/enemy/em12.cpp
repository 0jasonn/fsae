#include "engine/functions.h"
#include "enemy/em12.h"
#include "global.h"

// Original names: em12_init, em12_wait (em12_wait2 is in scratch/agentA/nonmatching/func_0203b594.c)

ARM void em12_init(Entity *e) {
    e->action = 1;
    e->unk_2e = 0xe;
    e->hitbox = data_020d2088;
    V(e)->w70.typeBits = ParseTypeBits(e->type);
    V(e)->areaX = ((e->x.HALF.HI & 0xfc0) >> 2) + data_0212c648.unk_18 + data_0213492c[e->unk_52 * 2];
    V(e)->areaW = ((((u32)e->x.HALF.HI) << 26) >> 22) + 0x20;
    V(e)->areaY = ((e->y.HALF.HI & 0xfc0) >> 2) + data_0212c648.unk_1a + data_0213492e[e->unk_52 * 2];
    V(e)->areaH = ((((u32)e->y.HALF.HI) << 26) >> 22) + 0x20;
    e->x.HALF.HI = (e->type2 << 4) + data_0212c648.unk_18 + data_0213492c[e->unk_52 * 2];
    V(e)->homeX = e->x.HALF.HI;
    e->y.HALF.HI = data_0212c648.unk_1a + (e->timer << 4) + data_0213492e[e->unk_52 * 2];
    V(e)->homeY = e->y.HALF.HI;
    func_0208ae30(e);
    e->spriteSettings.b20 = GetObjColor(data_020f26b8[data_0212c7c8.unk_1[0]]);
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

ARM void em12_wait(Entity *e) {
    if ((V(e)->w70.typeBits & data_02134954[e->unk_52]) == V(e)->w70.typeBits) {
        e->action = 2;
    }
}
