#include "engine/functions.h"
#include "global.h"

// Rr (rupee rush) actor (module rr). Address -> name:
//   0x02074cf8 rr_main (provisional name; dispatches on e->action)
//   0x02074d14 rr_init (original name)
//   0x02074d90 rr_wait (original name)
//   0x02074dc4 rr_move (original name)
//   0x02074e8c setRupee (original name)

extern const EntityFunc rr_actions[];         // rr_actions, indexed by e->action
extern const u8 setRupee_kindTable[];         // setRupee_kindTable, indexed by the kind index
extern u32 em12_typeMasks[];                  // indexed by e->areaIndex
extern const u32 flagBits[];                  // indexed by e->type2
extern u16 data_0213492c[];                   // per area x offset, u16 pairs
extern u16 em12_spawnOffsetY[];               // per area y offset, u16 pairs

void setRupee(Entity *e, u16 x, u16 y);

// File-local overlay of the rupee rush fields.
typedef struct Vars_Rr {
    /* 00 */ u8 unk_00[0x16];
    /* 16 */ u8 spawnLife;       // copied to the spawned object's timer by setRupee
    /* 17 */ u8 unk_17[0x60 - 0x17];
    /* 60 */ u32 typeBits;       // ParseTypeBits(e->type), tested against em12_typeMasks[e->areaIndex]
    /* 64 */ const u8 *cursor;   // walks (x, y) byte pairs from GetInfoAdrs(), 0xff ends the list
    /* 68 */ u8 kindIndex;       // (type2 >> 5) & 7, indexes setRupee_kindTable
    /* 69 */ u8 unk_69;
    /* 6a */ u16 layer;          // 0x4000 or 0x8000, copied to the spawned object's layer
} Vars_Rr;

ARM void rr_main(Entity *e) {
    rr_actions[e->action](e);
}

ARM void rr_init(Entity *e) {
    Vars_Rr *v;
    u16 layer;

    v = VARS(Vars_Rr, e);
    e->action++;
    v->typeBits = ParseTypeBits(e->type);
    v->cursor = GetInfoAdrs(e->areaIndex, e->timer);
    v->layer = (e->x.HALF.HI >> 8) & 1;
    e->subtimer = (u8)e->x.HALF.HI;
    v->spawnLife = (u8)e->y.HALF.HI;
    v->kindIndex = (e->type2 >> 5) & 7;
    e->type2 = e->type2 & 0x1f;
    layer = 0x4000;
    if (v->layer != 0) {
        layer = 0x8000;
    }
    v->layer = layer;
}

ARM void rr_wait(Entity *e) {
    Vars_Rr *v;

    v = VARS(Vars_Rr, e);
    if (v->typeBits == (v->typeBits & em12_typeMasks[e->areaIndex])) {
        e->action++;
        e->timer = e->subtimer;
    }
}

ARM void rr_move(Entity *e) {
    Vars_Rr *v;
    u16 x;
    u16 y;

    v = VARS(Vars_Rr, e);
    if (*v->cursor == 0xff) {
        em12_typeMasks[e->areaIndex] |= flagBits[e->type2];
        PutObjWork(e);
        return;
    }
    if (--e->timer != 0) {
        return;
    }
    e->timer = e->subtimer;
    x = (u16)((v->cursor[0] << 4 | 8) + data_0213492c[e->areaIndex * 2]);
    y = (u16)((v->cursor[1] << 4 | 8) + em12_spawnOffsetY[e->areaIndex * 2]);
    setRupee(e, x, y);
    v->cursor += 2;
}

// Spawns one rupee object at (x, y) for the rupee rush entity e.
ARM void setRupee(Entity *e, u16 x, u16 y) {
    Vars_Rr *v;
    Entity *spawn;

    v = VARS(Vars_Rr, e);
    spawn = GetSetWork(0, setRupee_kindTable[v->kindIndex], 1);
    if (spawn == NULL) {
        return;
    }
    spawn->x.HALF.HI = x;
    spawn->y.HALF.HI = y;
    spawn->timer = v->spawnLife;
    spawn->layer = v->layer;
    KemuriSet(spawn);
}
