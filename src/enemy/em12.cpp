#include "engine/functions.h"
#include "enemy/em12.h"
#include "global.h"

// Original names: em12_init, em12_wait (em12_wait2 is in scratch/agentA/nonmatching/em12_wait2.c)

ARM void em12_init(Entity *e) {
    e->action = 1;
    e->unk_2e = 0xe;
    e->hitbox = em12_hitbox;
    V(e)->w70.typeBits = ParseTypeBits(e->type);
    V(e)->areaX = ((e->x.HALF.HI & 0xfc0) >> 2) + data_0212c648.unk_18 + data_0213492c[e->areaIndex * 2];
    V(e)->areaW = ((((u32)e->x.HALF.HI) << 26) >> 22) + 0x20;
    V(e)->areaY = ((e->y.HALF.HI & 0xfc0) >> 2) + data_0212c648.unk_1a + em12_spawnOffsetY[e->areaIndex * 2];
    V(e)->areaH = ((((u32)e->y.HALF.HI) << 26) >> 22) + 0x20;
    e->x.HALF.HI = (e->type2 << 4) + data_0212c648.unk_18 + data_0213492c[e->areaIndex * 2];
    V(e)->homeX = e->x.HALF.HI;
    e->y.HALF.HI = data_0212c648.unk_1a + (e->timer << 4) + em12_spawnOffsetY[e->areaIndex * 2];
    V(e)->homeY = e->y.HALF.HI;
    func_0208ae30(e);
    e->spriteSettings.b20 = GetObjColor(em12_colorByPlayer[data_0212c7c8.unk_1[0]]);
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

ARM void em12_wait(Entity *e) {
    if ((V(e)->w70.typeBits & em12_typeMasks[e->areaIndex]) == V(e)->w70.typeBits) {
        e->action = 2;
    }
}
