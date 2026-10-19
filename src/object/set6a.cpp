#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// Set6a actor (module set6a). Address -> name:
//   0x02060de0 Set6a (original name)
//   0x02060e18 set6a_init, 0x02060e8c set6a_move, 0x02060fe8 set6a_move2 (original names)
//   0x020610b4 set6a_noop (provisional: a function that only returns)

typedef struct Vars_Set6a {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // bits from ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 64 */ u8 unk_64[0xe];
    /* 72 */ u16 counter72; // frames until the next step (reloaded with 0x2d0 / 0xf0)
    /* 74 */ const u16 *statePtr; // points at a u16 that set6a_move2 waits on (0xffff)
    /* 78 */ u16 t78; // countdown in set6a_move, preset to timer * 0x3c by set6a_init
    /* 7c */ Entity *next; // link used to keep the set on a stack of set entities
} Vars_Set6a;

extern const EntityFunc data_020d91e4[]; // indexed by e->action
extern u8 data_021349c0[];
extern u32 em12_typeMasks[]; // one mask per area
extern u32 flagBits[]; // one mask per type2
extern u16 data_0212c5bc;
extern Entity *data_0212c648;

void getDebu(Entity *e);
void getMgrInfo(Entity *e);
void mgrMove(Entity *e);

ARM void Set6a(Entity *e) {
    if (data_021349c0[1] != 0 && e->objId != 0x72) {
        return;
    }
    data_020d91e4[e->action](e);
}

ARM void set6a_init(Entity *e) {
    if (e->objId == 0x72) {
        e->action = 1;
        e->x.HALF.HI = 0x1f8;
        e->y.HALF.HI = 0x1f8;
        VARS(Vars_Set6a, e)->counter72 = 0xf0;
        VARS(Vars_Set6a, e)->typeBits = ParseTypeBits(e->type);
        VARS(Vars_Set6a, e)->t78 = e->timer * 0x3c;
    } else {
        e->action = 3;
        e->x.HALF.HI = 0x1f8;
        e->y.HALF.HI = 0x1f8;
        VARS(Vars_Set6a, e)->counter72 = 0xf0;
        data_0212c648 = e;
    }
}

ARM void set6a_move(Entity *e) {
    u32 bits;

    if (e->objId == 0x72) {
        bits = VARS(Vars_Set6a, e)->typeBits;
        if (bits != (bits & em12_typeMasks[e->areaIndex])) {
            return;
        }
        if (VARS(Vars_Set6a, e)->t78 == 0) {
            SoundReq(0x10);
            data_0212c648 = VARS(Vars_Set6a, e)->next;
            em12_typeMasks[e->areaIndex] |= flagBits[e->type2];
            PutObjWork(e);
            return;
        }
        if (VARS(Vars_Set6a, e)->t78 == (u16)(e->timer * 0x3c)) {
            VARS(Vars_Set6a, e)->next = data_0212c648;
            data_0212c648 = e;
            SoundReq(0x800d01a7);
        }
        VARS(Vars_Set6a, e)->t78--;
        if ((data_0212c5bc & 0xf) == 0) {
            getDebu(e);
        }
        VARS(Vars_Set6a, e)->counter72--;
        if (VARS(Vars_Set6a, e)->counter72 != 0) {
            return;
        }
        VARS(Vars_Set6a, e)->counter72 = 0x2d0;
        e->action = 2;
        getMgrInfo(e);
    } else {
        if ((data_0212c5bc & 0xf) == 0) {
            getDebu(e);
        }
        VARS(Vars_Set6a, e)->counter72--;
        if (VARS(Vars_Set6a, e)->counter72 != 0) {
            return;
        }
        VARS(Vars_Set6a, e)->counter72 = 0x2d0;
        e->action = 2;
        getMgrInfo(e);
    }
}

ARM void set6a_move2(Entity *e) {
    if (e->objId == 0x72) {
        if (VARS(Vars_Set6a, e)->t78 != 0) {
            VARS(Vars_Set6a, e)->t78--;
        }
        mgrMove(e);
        if (VARS(Vars_Set6a, e)->counter72 != 0) {
            VARS(Vars_Set6a, e)->counter72--;
        }
        if (*VARS(Vars_Set6a, e)->statePtr != 0xffff) {
            return;
        }
        if (VARS(Vars_Set6a, e)->counter72 == 0) {
            e->action = 1;
            VARS(Vars_Set6a, e)->counter72 = 0xf0;
            return;
        }
        getMgrInfo(e);
    } else {
        mgrMove(e);
        if (VARS(Vars_Set6a, e)->counter72 != 0) {
            VARS(Vars_Set6a, e)->counter72--;
        }
        if (*VARS(Vars_Set6a, e)->statePtr != 0xffff) {
            return;
        }
        if (VARS(Vars_Set6a, e)->counter72 == 0) {
            e->action = 1;
            VARS(Vars_Set6a, e)->counter72 = 0xf0;
            return;
        }
        getMgrInfo(e);
    }
}

ARM void set6a_noop(Entity *e) {
}
