#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/g_callees.h"
#include "actor/object/actor_calls_k.h"

typedef struct Vars_RcYuka {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 moveCheckMask; // bit i set: player i rides the floor (low 4 bits)
    /* 64 */ u8 unk_64[0x18];
    /* 7c */ u16 prevX; // position at the start of the frame
    /* 7e */ u16 prevY;
} Vars_RcYuka;

extern "C" void Knife_Single_SinglePlay_SetObjMoveReqFlag(u8 *self, Entity *e, u32 mask, s32 a, u8 b);

#define RC_MOVE_PLAYERS(dir)                              \
    if (mask & 1) func_020852f8(playerWork[0].entity, dist, dir); \
    if (mask & 2) func_020852f8(playerWork[1].entity, dist, dir); \
    if (mask & 4) func_020852f8(playerWork[2].entity, dist, dir); \
    if (mask & 8) func_020852f8(playerWork[3].entity, dist, dir);

void rc_yukaMove(Entity *e) {
    Vars_RcYuka *v;
    void *bgBuffer;
    u8 dir;
    u8 mask;
    u32 dist;
    v = VARS(Vars_RcYuka, e);
    bgBuffer = (void *)GetBgBuffAdrs(e->layer);
    v->prevX = e->x.HALF.HI;
    v->prevY = e->y.HALF.HI;
    mask = v->moveCheckMask & 0xf;
    e->wallFlags = 0;
    if (mask == 0) {
        return;
    }
    dir = e->direction >> 2;
    switch (dir) {
    case 0:
    case 1:
        ue_bgcheck(e, bgBuffer);
        func_0208530c(e, e->speed, 0, e->wallFlags);
        dist = ((u32)(v->prevY - e->y.HALF.HI) << 24) >> 16;
        if (dist != 0) {
            RC_MOVE_PLAYERS(0)
        }
        Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, 0);
        if (dir != 1) {
            break;
        }
    case 2:
    case 3:
        migi_bgcheck(e, bgBuffer);
        func_0208530c(e, e->speed, 8, e->wallFlags);
        dist = ((u32)(e->x.HALF.HI - v->prevX) << 24) >> 16;
        if (dist != 0) {
            RC_MOVE_PLAYERS(8)
        }
        Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, 8);
        if (dir != 3) {
            break;
        }
    case 4:
    case 5:
        shita_bgcheck(e, bgBuffer);
        func_0208530c(e, e->speed, 0x10, e->wallFlags);
        dist = ((u32)(e->y.HALF.HI - v->prevY) << 24) >> 16;
        if (dist != 0) {
            RC_MOVE_PLAYERS(0x10)
        }
        Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, 0x10);
        if (dir != 5) {
            break;
        }
    case 6:
    case 7:
        hidari_bgcheck(e, bgBuffer);
        func_0208530c(e, e->speed, 0x18, e->wallFlags);
        dist = ((u32)(v->prevX - e->x.HALF.HI) << 24) >> 16;
        if (dist != 0) {
            RC_MOVE_PLAYERS(0x18)
        }
        Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, 0x18);
        if (dir != 7) {
            break;
        }
        ue_bgcheck(e, bgBuffer);
        func_0208530c(e, e->speed, 0, e->wallFlags);
        dist = ((u32)(v->prevY - e->y.HALF.HI) << 24) >> 16;
        if (dist != 0) {
            RC_MOVE_PLAYERS(0)
        }
        Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, dist, 0);
        break;
    }
}
