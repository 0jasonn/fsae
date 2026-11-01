#include "engine/functions.h"
#include "actor/object/matsuri.h"
#include "global.h"

// Matsuri actor, first unit (module matsuri). Address -> name:
//   0x02059b24 matsuri (provisional, matsuri_actions[e->action](e))
//   0x02059b40 matsuri_init (original name)

void matsuri(Entity *e) {
    matsuri_actions[e->action](e);
}

void matsuri_init(Entity *e) {
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

// Matsuri actor, second unit (module matsuri). Address -> name:
//   0x02059be4 matsuri_wait (original name)
//   0x02059c30 matsuri_ma (original name)
//   0x02059c58 matsuri_ma2 (original name)
//   0x02059c78 matsuri_move (original name)

void matsuri_wait(Entity *e) {
    if ((VMATSURI(e)->typeBits & em12_typeMasks[e->areaIndex]) != VMATSURI(e)->typeBits) {
        return;
    }
    SoundReq(0x800d01a7);
    e->action++;
    e->timer = 0x3c;
}

void matsuri_ma(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action++;
        e->timer = 0x3c;
    }
}

void matsuri_ma2(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action++;
    }
}

void matsuri_move(Entity *e) {
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
