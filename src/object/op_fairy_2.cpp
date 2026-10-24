#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Opening fairy actor, init and states (module op_fairy). Address -> name:
//   (op_fairy_init at 0x0205f480 is parked in scratch/agentC/nonmatching)
//   0x0205f524 fairy_move (original name)
//   0x0205f560 fairy_fuwafuwa_05f560 (original name fairy_fuwafuwa)
//   0x0205f610 fairy_talk (original name)
//   0x0205f670 op_bikkuri (original name)
//   0x0205f6f4 op_sword (original name)
//   (ed_fairy at 0x0205f78c is in ed_fairy_1.cpp)

extern u16 data_02115990[]; // start x per type
extern u16 data_021159ac[][2]; // bounds per type, passed to ObjAnimMoveSet
extern u8 data_0211598c[4]; // direction offsets, indexed by Random() & 3
extern u32 data_02134924[]; // event flags (bit 0 and bit 1 are read)

// Opening fairy fields past the shared header
typedef struct Vars_Fairy {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ s16 homeX; // position the fairy flies back to
    /* 62 */ s16 homeY;
} Vars_Fairy;

ARM void fairy_move(Entity *e) {
    Vars_Fairy *v = VARS(Vars_Fairy, e);

    UpdateAnimationSingleFrame(e);
    if (ObjAnimMoveLine(e) == 0) {
        return;
    }
    e->action = e->action + 1;
    v->homeX = e->x.HALF.HI;
    v->homeY = e->y.HALF.HI;
}

ARM void fairy_fuwafuwa_05f560(Entity *e) {
    Vars_Fairy *v = VARS(Vars_Fairy, e);
    u8 timer;

    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if ((u16)(v->homeX - e->x.HALF.HI) > 0xc || (u16)(v->homeY - e->y.HALF.HI) > 0xc) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, v->homeX, v->homeY);
        e->direction = (e->direction + data_0211598c[Random() & 3]) & 0x1f;
    }
    timer = e->timer;
    e->z.HALF.HI = (s16)(((s32)trigTable[timer + 0x40] << 2) >> 8);
    e->timer = timer + 1;
}

ARM void fairy_talk(Entity *e) {
    u8 timer;

    UpdateAnimationSingleFrame(e);
    UpdateAnimationSingleFrame(e);
    timer = e->timer;
    e->z.HALF.HI = (s16)(((s32)trigTable[timer + 0x40] << 2) >> 8);
    e->timer = timer + 0x10;
    if (data_021349c0[0xf] != e->type2) {
        e->action = 2;
    }
}

ARM void op_bikkuri(Entity *e) {
    switch (e->action) {
    case 0:
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b30 = 0;
        e->action = e->action + 1;
        e->spriteSettings.b14 = 0;
        if (e->timer != 0) {
            SoundReq(0x21e);
        } else {
            SoundReq(0x1f6);
        }
        return;
    case 1:
        e->type2 = e->type2 - 1;
        if (e->type2 != 0) {
            return;
        }
        PutObjWork(e);
        return;
    }
}

ARM void op_sword(Entity *e) {
    switch (e->action) {
    case 0:
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b30 = 2;
        e->action = e->action + 1;
        e->spriteSettings.b14 = 1;
        return;
    case 1:
        if ((data_02134924[0] & 1) == 0) {
            return;
        }
        e->action = e->action + 1;
        e->unk_21 = 1;
        SoundReq(0x1f5);
        return;
    case 2:
        if ((data_02134924[0] & 2) == 0) {
            return;
        }
        PutObjWork(e);
        return;
    }
}
