#include "engine/functions.h"
#include "object/matsuri.h"
#include "global.h"

// Matsuri actor, second unit (module matsuri). Address -> name:
//   0x02059be4 matsuri_wait (original name)
//   0x02059c30 matsuri_ma (original name)
//   0x02059c58 matsuri_ma2 (original name)
//   0x02059c78 matsuri_move (original name)

ARM void matsuri_wait(Entity *e) {
    if ((VMATSURI(e)->typeBits & em12_typeMasks[e->areaIndex]) != VMATSURI(e)->typeBits) {
        return;
    }
    SoundReq(0x800d01a7);
    e->action++;
    e->timer = 0x3c;
}

ARM void matsuri_ma(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action++;
        e->timer = 0x3c;
    }
}

ARM void matsuri_ma2(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action++;
    }
}

ARM void matsuri_move(Entity *e) {
    Entity *child;
    u16 count;
    u16 rangeX;
    u16 rangeY;
    u32 offsetX;
    u32 offsetY;

    count = VMATSURI(e)->spawnCount;
    VMATSURI(e)->spawnCount = count - 1;
    if (count != 0) {
        if (Random() & 7) {
            return;
        }
        if (data_0212c4f4 >= 0x70) {
            return;
        }
        child = GetSetWork(0, (u8)e->y.HALF.HI, 1);
        if (child == NULL) {
            return;
        }
        rangeX = VMATSURI(e)->rangeX;
        rangeY = VMATSURI(e)->rangeY;
        offsetX = (Random() % (u32)rangeX) * 16 + 8;
        offsetY = (Random() % (u32)rangeY) * 16 + 8;
        child->x.HALF.HI = VMATSURI(e)->baseX + offsetX;
        child->y.HALF.HI = VMATSURI(e)->baseY + offsetY;
        child->areaIndex = e->areaIndex;
        child->timer = 3;
        child->layer = e->layer;
        KemuriSet(child);
        func_0208ae78(child);
    } else {
        em12_typeMasks[e->areaIndex] |= flagBits[e->type2];
        PutObjWork(e);
    }
}
