#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_a.h"

extern EntityFunc plateTable[];        // plateTable
extern EntityFunc kumo0Table[];        // kumo0Table
extern EntityFunc keyKazanTable[];     // keyKazanTable
extern s16 data_02115c78[];           // shared with door_silver_init, [type][3] flat
extern s16 kumo0InitTable[];          // kumo0InitTable, [type][3] flat
extern u8 keyInitUnk21Table[];         // keyInitUnk21Table, indexed by type2
extern u8 keyInitBankTable[];          // keyInitBankTable, indexed by type2
extern const s16 trigTable[];
extern u16 data_0212c594[];
extern u8 data_021349c0[];

void key_pos_set(Entity *e);

// Actor fields of the key family, file-local.
typedef struct Vars_Key {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u8 posIndex; // index into trigTable for the position on the key's circle
} Vars_Key;

// key_silver, 0x020695c8
ARM void key_silver(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    s16 *pos;
    if (action != 0) {
        return;
    }
    nextAction = action + 1;
    e->action = nextAction;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 1;
    pos = data_02115c78 + e->type * 3;
    e->x.HALF.HI = pos[0];
    e->y.HALF.HI = pos[1];
    e->unk_21 = pos[2];
}

// key_plate, 0x02069630
ARM void key_plate(Entity *e) {
    plateTable[e->action](e);
}

// key_plate_init, 0x0206964c
ARM void key_plate_init(Entity *e) {
    u8 action = e->action;
    u8 nextAction;
    s16 *pos;
    nextAction = action + 1;
    e->action = nextAction;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    e->spriteSettings.b0 = 2;
    pos = data_02115c78 + e->type * 3;
    e->x.HALF.HI = pos[0];
    e->y.HALF.HI = pos[1];
    e->unk_21 = pos[2];
}

// plate_appear, 0x020696a8
ARM void plate_appear(Entity *e) {
    e->y.HALF.HI += 4;
    if (e->y.HALF.HI < 8) {
        return;
    }
    e->y.HALF.HI = 8;
    e->action++;
    e->timer = 0x5a;
}

// plate_wait, 0x020696e0
ARM void plate_wait(Entity *e) {
    e->timer--;
    if (e->timer == 0) {
        e->action++;
    }
}

// plate_out, 0x02069700
ARM void plate_out(Entity *e) {
    e->y.HALF.HI -= 4;
    if (e->y.HALF.HI >= -0x20) {
        return;
    }
    PutObjWork(e);
}

// kumo0, 0x02069724
ARM void kumo0(Entity *e) {
    kumo0Table[e->action](e);
}

// kumo0_init, 0x02069740
ARM void kumo0_init(Entity *e) {
    u8 nextAction = e->action + 1;
    e->action = nextAction;
    e->spriteSettings.b0 = 2;
    e->spriteSettings.b30 = 3;
    e->spriteSettings.b14 = 3;
    e->direction = 8;
    e->speed = (Random() & 0x3f) + 0x40;
    e->unk_21 = kumo0InitTable[e->type * 3];
}

// kumo0_move, 0x020697ac
ARM void kumo0_move(Entity *e) {
    MoveDir(e);
    if (e->x.HALF.HI > 0x140) {
        e->x.HALF.HI = -0x80;
    }
}

// key_kazan, 0x020697cc
ARM void key_kazan(Entity *e) {
    keyKazanTable[e->action](e);
}

// key_pos_set, 0x020697e8
ARM void key_pos_set(Entity *e) {
    u8 index = VARS(Vars_Key, e)->posIndex;
    u8 scale = data_021349c0[9];
    e->x.HALF.HI = ((scale * trigTable[index + 0x40]) >> 8) + 0x80;
    e->y.HALF.HI = ((scale * trigTable[index]) >> 8) + 0x6c;
}

