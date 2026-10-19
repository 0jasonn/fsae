#include "enemy/actor_0204112c.h"
#include "global.h"

extern const u32 data_020cf9b8[];

// Enemy_SelectActionFromParentBit (0x02042798): when the parent's low flags are clear, picks action 0xa or 0xd
// from the parent bit in data_020cf9b8.
ARM void Enemy_SelectActionFromParentBit(Entity *e) {
    u8 parentFlags = e->parent->unk_6c[4];
    if (parentFlags & 3) {
        return;
    }
    if (parentFlags & data_020cf9b8[e->type2 + 2]) {
        e->action = 0xa;
    } else {
        e->action = 0xd;
    }
}

// Enemy_FinishOnFlagWithTimer (0x020427d4): on an odd frame, finishes when Enemy_SpawnPartPairWithSfx succeeds and starts
// a 0x12c-frame delay.
ARM void Enemy_FinishOnFlagWithTimer(Entity *e) {
    if (e->frame & 1) {
        if (Enemy_SpawnPartPairWithSfx(e) == 0) {
            return;
        }
        e->action = 0xb;
        VT(e)->delay = 0x12c;
        VT(e)->stateCounter = 0;
        return;
    }
    UpdateAnimationSingleFrame(e);
}
