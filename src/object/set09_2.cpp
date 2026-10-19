#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Set09 actor, second unit (module set09). Address -> name:
//   0x02062ce4 set09_wait, 0x02062d90 set09_initset, 0x02062dc4 set09_move, 0x02062e14 set09_wait2 (original names)

typedef struct Vars_Set09 {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 unk_62; // counter, incremented by set6b_setenemy
    /* 64 */ u16 unk_64; // index passed to CountBits / func_02084634
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 typeBits; // bits from ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 6c */ u8 unk_6c[4];
    /* 70 */ const u16 *info; // table from GetInfoAdrs, 8-byte entries ended by 0xffff
} Vars_Set09;

extern const EntityFunc data_020d9f38[]; // indexed by e->action
extern u32 em12_typeMasks[]; // one mask per area
extern "C" void GetCellsInRandomSet(u16 cell, u16 w, u16 h);
void BgmSet(void);
void set6b_setenemy(Entity *e, u8 index);
extern u32 flagBits[]; // one bit word per type2 bit (0x1f)

ARM void set09_wait(Entity *e) {
    if (VARS(Vars_Set09, e)->typeBits != (VARS(Vars_Set09, e)->typeBits & em12_typeMasks[e->areaIndex])) {
        return;
    }
    if (e->objId != 0x70 && e->objId != 0x71) {
        SoundReq(0x80020000);
        SoundReq(0x800d01a7);
    }
    if (e->unk_16 != 0) {
        if (e->objId != 0x70 && e->objId != 0x71) {
            SoundReq(0x1a1);
            data_0212c7c8.unk_26 = 0x1a1;
        }
        if (e->objId == 9) {
            u8 count52 = ((u8 *)&data_0212c7c8)[0x52];
            ((u8 *)&data_0212c7c8)[0x52] = count52 + 1;
        }
    }
    e->action = 2;
}

ARM void set09_initset(Entity *e) {
    if (CountBits(VARS(Vars_Set09, e)->unk_64) >= e->timer) {
        e->action = 3;
        return;
    }
    set6b_setenemy(e, 0);
}

ARM void set09_move(Entity *e) {
    if (CountBits(VARS(Vars_Set09, e)->unk_64) < e->timer) {
        set6b_setenemy(e, 0x5a);
    }
    if (e->x.HALF.HI == 0) {
        return;
    }
    e->x.HALF.HI = e->x.HALF.HI - 1;
    if (e->x.HALF.HI == 0) {
        e->action = 4;
    }
}

ARM void set09_wait2(Entity *e) {
    if (VARS(Vars_Set09, e)->unk_62 == 0) {
        e->action = 5;
        e->timer = 0x3c;
    }
}
