#include "engine/functions.h"
#include "game/rankingsave.h"
#include "global.h"
#include "game/savemedia.h"

// Set actor unit 6 (module set). Address -> name (original names where listed in symbols.txt):
//   0x02057cec set0a_move
//   0x02057d58 set0a_moveset
//   0x02057dec set0a_setenemy

// File-local fields of the set actors (Entity bytes from 0x6c on).
typedef struct SetVars {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u16 retainFlag;
    /* 6e */ u8 unk_6e[2];
    /* 70 */ u8 setKind;
    /* 71 */ u8 setParam1;
    /* 72 */ u8 setParam2;
} SetVars;

extern const u8 data_020d87a0[];

ARM void set0a_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame == 1) {
        set0a_setenemy(e);
        return;
    }
    if (e->frame & 0x80) {
        PutObjWork(e);
        return;
    }
    if ((e->frame & 0x40) == 0) {
        return;
    }
    e->frame = 0;
    if (e->subtimer == 0) {
        EnqueueSFX(0x74);
    } else {
        EnqueueSFX(0x9d);
    }
}

ARM void set0a_moveset(Entity *e) {
    e->action = 2;
    if (VARS(SetVars, e)->setKind != 0x12) {
        if (e->x.HALF.HI != 0 || e->y.HALF.HI != 0) {
            e->spriteSettings.b0 = 1;
        }
    }
    if (func_02084670(data_020d87a0, VARS(SetVars, e)->setKind)) {
        e->subtimer = 1;
        e->unk_20 = 0xf4;
        e->spriteSettings.b16 = 1;
        e->spriteSettings.b6 = 2;
        e->unk_1b = 0x91;
    }
    InitAnimationForceUpdate(e, 0);
}

ARM void set0a_setenemy(Entity *e) {
    Entity *child = GetObjWork();

    if (child == 0) {
        return;
    }
    child->objKind = 3;
    child->objId = VARS(SetVars, e)->setKind;
    child->type = VARS(SetVars, e)->setParam1;
    child->type2 = VARS(SetVars, e)->setParam2;
    child->timer = e->timer;
    EmPalamCopy(e, child);
    RegistObjWork(4, child);
    e->frame = 0;
}
