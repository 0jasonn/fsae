#include "engine/functions.h"
#include "object/matsuri.h"
#include "global.h"

// Matsuri actor, first unit (module matsuri). Address -> name:
//   0x02059b24 matsuri (provisional, matsuri_actions[e->action](e))
//   0x02059b40 matsuri_init (original name)

ARM void matsuri(Entity *e) {
    matsuri_actions[e->action](e);
}

ARM void matsuri_init(Entity *e) {
    u32 bits;

    VMATSURI(e)->typeBits = ParseTypeBits(e->type);
    e->action++;
    bits = (u32)GetInfoAdrs(e->areaIndex, e->timer);
    VMATSURI(e)->baseX = data_0213492c[e->areaIndex * 2] + ((bits & 0xff) << 4);
    bits = bits >> 8;
    VMATSURI(e)->baseY = em12_spawnOffsetY[e->areaIndex * 2] + ((bits & 0xff) << 4);
    bits = bits >> 8;
    VMATSURI(e)->rangeX = bits & 0xff;
    bits = bits >> 8;
    VMATSURI(e)->rangeY = bits & 0xff;
    if (e->y.HALF.HI == 0) {
        e->y.HALF.HI = 2;
    }
    VMATSURI(e)->spawnCount = e->x.HALF.HI * 0x3c;
}
