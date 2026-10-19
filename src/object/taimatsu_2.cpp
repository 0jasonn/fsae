#include "engine/functions.h"
#include "object/taimatsu.h"
#include "global.h"

// Taimatsu puzzle actor, second unit (module taimatsu). Address -> name:
//   0x02059804 tp00_move (original name)
//   0x0205982c taimatsu_puzzle_01 (original name)
//   0x02059848 tp01_wait (original name)
//   0x02059878 tp01_init (original name)
//   0x02059898 tp01_move (original name)
//   0x02059950 tp01_check (original name)
//   0x02059a28 make_question (original name)
//   0x02059a74 taimatsu_count (original name)
//   0x02059ae8 taimatsu_clear (original name)

ARM void tp00_move(Entity *e) {
    if ((em12_typeMasks[e->areaIndex] & 3) != 3) {
        e->action--;
    }
}

ARM void taimatsu_puzzle_01(Entity *e) {
    taimatsu01_actions[e->action](e);
}

ARM void tp01_wait(Entity *e) {
    u32 flags;

    flags = em12_typeMasks[e->areaIndex];
    if (((flags & 0x14) == 0x14) || (flags & 0x40)) {
        PutObjWork(e);
    }
}

ARM void tp01_init(Entity *e) {
    e->timer = 0x3c;
    e->subtimer = 0;
    e->action++;
}

ARM void tp01_move(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->timer = 0x3c;
    SoundReq(0x2a);
    RewCell(0x10e, VTP00(e->contactedEntity)->packed[e->subtimer], e->layer);
    e->subtimer++;
    if (e->subtimer < 6) {
        return;
    }
    e->timer = taimatsu_count(e);
    if (e->timer == 0) {
        e->action++;
        return;
    }
    SoundReq(3);
    em12_typeMasks[e->areaIndex] |= 4;
    taimatsu_clear(e);
    e->action = 0;
}

ARM void tp01_check(Entity *e) {
    u8 count;
    u16 *table;

    count = taimatsu_count(e);
    if (count != e->timer) {
        table = (u16 *)e->contactedEntity->unk_6c;
        while (e->timer != count) {
            if (func_02083ca8(table[e->timer], e->layer) == 0x10e) {
                SoundReq(9);
                e->timer++;
            } else {
                SoundReq(3);
                em12_typeMasks[e->areaIndex] |= 4;
                taimatsu_clear(e->contactedEntity);
                e->action = 0;
                return;
            }
        }
    }
    if (e->timer == 6) {
        SoundReq(0x10);
        em12_typeMasks[e->areaIndex] |= 8;
        e->action = 0;
    }
}

ARM void make_question(Entity *e) {
    u32 i;
    u32 j;
    u16 tmp;

    i = 5;
    do {
        j = Random() % (u32)i;
        tmp = VTP00(e)->packed[i];
        VTP00(e)->packed[i] = VTP00(e)->packed[j];
        VTP00(e)->packed[j] = tmp;
        tmp = VTP00(e)->packed[i + 6];
        VTP00(e)->packed[i + 6] = VTP00(e)->packed[j + 6];
        VTP00(e)->packed[j + 6] = tmp;
        i--;
    } while (i != 0);
}

ARM u8 taimatsu_count(Entity *e) {
    u16 *table;
    u8 count;
    u8 i;

    count = 0;
    e->type2 = 0;
    table = (u16 *)e->contactedEntity->unk_6c;
    for (i = 0; i < 6; i++) {
        if (func_02083ca8(table[i], e->layer) == 0x10e) {
            e->type2 |= 1 << i;
            count++;
        }
    }
    return count;
}

ARM void taimatsu_clear(Entity *e) {
    u8 i;

    for (i = 0; i < 12; i++) {
        RewCell(0x10d, VTP00(e)->packed[i], e->layer);
    }
}
