#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/set58.h"
#include "object/d_decls.h"

// Set58 kougyoku (crystal ball) and kougyoku2 actors (module set58, unit 9). Address -> name:
//   0x02073e18 set58_kougyoku (original name; type2 == 0 uses one action table, otherwise the kougyoku2 table)
//   0x02073e60 kougyoku_init (original name)
//   0x02073efc kougyoku_move (original name)
//   0x02073fe4 kougyoku_wait (original name)
//   0x02074020 kougyoku_down (original name)
//   0x02074054 kougyoku2_move (original name)
//   0x020740b0 kougyoku2_wait (original name)
//   0x020740e0 kougyoku2_down (original name)
//   0x0207415c kougyoku2_key (original name)
//   0x0207417c set58_fairy (original name; dispatches on e->action)
//   0x02074198 kougyoku2_fairy_init (original name)
//   0x02074218 kougyoku2_fairy_fuwafuwa (original name)

extern const EntityFunc set58_kougyokuActions[];  // set58_kougyokuActions, indexed by e->action
extern const EntityFunc set58_kougyoku2Actions[]; // set58_kougyoku2Actions, indexed by e->action
extern const u16 set58_kougyokuTable[];           // set58_kougyokuTable, indexed by rank
extern const EntityFunc set58_fairyActions[];     // set58_fairyActions, indexed by e->action
extern const u8 set58_fairyDirOffsets[];          // set58_fairyDirOffsets, indexed by Random() & 3
extern const s16 trigTable[];                     // trigTable (trigTable), indexed by timer + 0x40

// Fairy spot: the fairy floats around the point it was spawned at.
typedef struct Vars_Set58Fairy {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ s16 homeX; // x of the spot
    /* 62 */ s16 homeY; // y of the spot
} Vars_Set58Fairy;

ARM void set58_kougyoku(Entity *e) {
    if (e->type2 == 0) {
        set58_kougyokuActions[e->action](e);
    } else {
        set58_kougyoku2Actions[e->action](e);
        UpdateAnimationSingleFrame(e);
    }
}

ARM void kougyoku_init(Entity *e) {
    s32 rank;

    set58_actionInit(e);
    e->spriteSettings.b0 = 1;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b14 = 0;
    e->unk_5e.b0 = 3;
    e->speed = 0x80;
    e->direction = 0x10;
    rank = RankCheck();
    if (rank == 3) {
        rank = (u8)(rank + data_0212c7c8.unk_1[0]);
    }
    e->spriteSettings.b20 = set58_kougyokuTable[rank];
    e->spriteSettings.b16 = e->spriteSettings.b20;
}

ARM void kougyoku_move(Entity *e) {
    u16 i;
    Entity *child;

    if (e->type2 == 0 && e->unk_16 == 0) {
        e->unk_16 = 1;
        SoundReq(0x215);
    }
    UpdateAnimationSingleFrame(e);
    MoveDir(e);
    if (e->parent->y.HALF.HI + 0x18 != e->y.HALF.HI) {
        return;
    }
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        child = GetSetWork(0x58, 9, 1);
        if (child != NULL) {
            ObjPosCopy(e, child);
            child->child = data_0212ceb0[i].entity;
        }
    }
    e->action = 2;
    e->timer = 0x5a;
    e->spriteSettings.b0 = 0;
}

ARM void kougyoku_wait(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->action = 3;
    e->timer = 0x3c;
    em12_typeMasks |= 4;
}

ARM void kougyoku_down(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    em12_typeMasks |= 8;
    PutObjWork(e);
}

ARM void kougyoku2_move(Entity *e) {
    Entity *child;

    child = e->child;
    if (child->x.HALF.HI == e->x.HALF.HI && child->y.HALF.HI - 0x20 == e->y.HALF.HI) {
        e->action = 2;
        return;
    }
    e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, child->x.HALF.HI, child->y.HALF.HI - 0x20);
    MoveDir(e);
}

ARM void kougyoku2_wait(Entity *e) {
    if (!(em12_typeMasks & 4)) {
        return;
    }
    e->action = 3;
    e->timer = 0x14;
    e->direction = 0x10;
}

ARM void kougyoku2_down(Entity *e) {
    Entity *child;

    if (e->timer != 0) {
        e->timer--;
        MoveDir(e);
        return;
    }
    if (!(em12_typeMasks & 8)) {
        return;
    }
    child = GetSetWork(0x59, 0, 0);
    if (child == NULL) {
        return;
    }
    ObjPosCopy(e, child);
    child->y.WORD += 1;
    e->action = 4;
    e->timer = 0x3c;
}

ARM void kougyoku2_key(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    PutObjWork(e);
}

ARM void set58_fairy(Entity *e) {
    set58_fairyActions[e->action](e);
}

ARM void kougyoku2_fairy_init(Entity *e) {
    Vars_Set58Fairy *v = VARS(Vars_Set58Fairy, e);

    e->spriteSettings.b0 = 1;
    e->spriteSettings.b30 = 1;
    e->spriteSettings.b14 = 0;
    v->homeX = e->x.HALF.HI;
    v->homeY = e->y.HALF.HI;
    e->direction = Random() & 0x1f;
    e->speed = 0x20;
    set58_actionInit(e);
    if (func_02081b64() != 0) {
        e->spriteSettings.b16 = e->spriteSettings.b16 + 1;
    }
}

ARM void kougyoku2_fairy_fuwafuwa(Entity *e) {
    Vars_Set58Fairy *v = VARS(Vars_Set58Fairy, e);

    MoveDir(e);
    UpdateAnimationSingleFrame(e);
    if ((u16)(v->homeX - e->x.HALF.HI) > 12 || (u16)(v->homeY - e->y.HALF.HI) > 12) {
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, v->homeX, v->homeY);
        e->direction = (e->direction + set58_fairyDirOffsets[Random() & 3]) & 0x1f;
    }
    e->z.HALF.HI = ((trigTable[e->timer + 0x40] << 2) >> 8) - 8;
    e->timer++;
}
