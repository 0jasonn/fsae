#include "engine/functions.h"
#include "engine/player.h"
#include "actor/object/rewhalf.h"
#include "actor/object/set30_2.h"
#include "game/frame_load.h"
#include "global.h"

// set30_init (0x02068e18): sets up the actor (type2 keeps its low two bits, bit 7 becomes typeFlag) and picks its
// vgroup from the per-stage table (data_020da714) or, from stage 5 on, from the current frame's roomNo (data_020da754).
void set30_init(Entity *e) {
    if ((e->type2 & 0x7f) == 3) {
        e->type2 = (e->type2 & 0x80) | (gameState.playerCount - 2);
    }
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_5e.b0 = 0;
    e->hitbox = set30Hitbox;
    func_0208ae78(e);
    InitAnimationForceUpdate(e, 0);
    VARS(Vars_Set30, e)->typeFlag = e->type2 >> 7;
    e->type2 = e->type2 & 3;
    e->spriteSettings.b14 = 2;
    if (gameState.active != 0) {
        GetVGroup(e, data_020da714[e->type2 + 0xc]);
        return;
    }
    if (gameState.unk_01 >= 5) {
        const FRAME_INFO_ *frame = bgmIndexTable[gameState.unk_01][gameState.unk_48].frame;
        GetVGroup(e, data_020da754[e->type2 + frame->roomNo * 3]);
    } else {
        GetVGroup(e, data_020da714[e->type2 + gameState.unk_01 * 3]);
    }
}

// set30_wait (0x02068f58): compares the number of agreeing players (motiagecheck) with the animation state. When all
// are there (type2 + 2) the flag bit is set and the actor switches to action 2; otherwise the animation follows the
// count up or down.
void set30_wait(Entity *e) {
    u8 check = motiagecheck(e);
    if (check >= e->type2 + 2) {
        em12_typeMasks[e->areaIndex] |= flagBits[e->type];
        e->action = 2;
        e->subtimer = 0;
        e->z.HALF.HI = 0;
        e->animationState = 4;
        InitAnimationForceUpdate(e, 4);
        EnqueueSFX(0x71);
        return;
    }
    if (check > e->animationState) {
        if (e->type2 + 1 == check) {
            e->subtimer = 4;
            InitAnimationForceUpdate(e, check + 1);
        } else {
            InitAnimationForceUpdate(e, check);
        }
        EnqueueSFX(0x12);
    } else {
        if (check < e->animationState) {
            InitAnimationForceUpdate(e, check);
        }
    }
    e->animationState = check;
}

// set30_move (0x02069030): once typeFlag is set, starts the action when the agreeing count is still below type2 + 2.
void set30_move(Entity *e) {
    int state;
    if (VARS(Vars_Set30, e)->typeFlag == 0) {
        return;
    }
    state = motiagecheck(e);
    if (state >= 2 + e->type2) {
        return;
    }
    e->action = 1;
    e->animationState = state;
    em12_typeMasks[e->areaIndex] ^= flagBits[e->type];
    InitAnimationForceUpdate(e, e->animationState);
}
