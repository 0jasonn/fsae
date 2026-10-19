#include "engine/functions.h"
#include "global.h"
#include "object/setmisc.h"

// Set08 actor (module set08). Address -> name:
//   0x02061be8 Set08 (original name)
//   0x02061c04 set08_init, 0x02061c64 set08_wait, 0x02061cb4 set08_open, 0x02061cf4 set08_move (original names)

typedef struct Vars_Set08 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // bits from ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 64 */ u8 unk_64[0x14];
    /* 78 */ u16 cell; // door cell, computed from the position relative to the scroll
} Vars_Set08;

typedef struct UnkStruct_0212c648_T {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} UnkStruct_0212c648_T;

extern UnkStruct_0212c648_T data_0212c648;
extern const EntityFunc data_020d92c0[]; // indexed by e->action
extern u32 em12_typeMasks[]; // one mask per area

void doorCheck(Entity *e);
void srchDoor(Entity *e);
void rewHalf(Entity *e);
void set6b_rewDoor(Entity *e);

ARM void Set08(Entity *e) {
    data_020d92c0[e->action](e);
}

ARM void set08_init(Entity *e) {
    e->action = 1;
    e->timer = 0x18;
    VARS(Vars_Set08, e)->typeBits = ParseTypeBits(e->type);
    VARS(Vars_Set08, e)->cell = ((e->x.HALF.HI - data_0212c648.scrollX) >> 4) |
                                (((e->y.HALF.HI - data_0212c648.scrollY) >> 4) << 6);
    doorCheck(e);
}

ARM void set08_wait(Entity *e) {
    u32 bits;

    if (e->type2 & 0x80) {
        e->action = 2;
        srchDoor(e);
        return;
    }
    bits = VARS(Vars_Set08, e)->typeBits;
    if (bits != (bits & em12_typeMasks[e->areaIndex])) {
        return;
    }
    e->action = 2;
    srchDoor(e);
}

ARM void set08_open(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action = 3;
        return;
    }
    if (e->timer != 0xc) {
        return;
    }
    rewHalf(e);
    func_02085f98(e, 0x11);
}

ARM void set08_move(Entity *e) {
    set6b_rewDoor(e);
    PutObjWork(e);
}
