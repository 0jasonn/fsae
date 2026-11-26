#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/enemy/em0e_units.h"
#include "actor/enemy/em0e.h"

// Actor em0e, hippariCheck (0x0202d5bc, after em0e_4.cpp): the tug of war over a type 2 group.

extern const u8 em0e_pullStrengthTable[]; // em0e_pullStrengthTable: knockback of a released puller, indexed by distance >> 2

// partFlags holds the two pullers (bits 0-1 and 4-5: player index; bits 2-3 and 6-7: which side pulls). With one
// side pulling, that player drags its part (and the group) while the pieces are together and is released with a
// knockback once they are apart; with both pulling, the pieces are pulled apart and the group stays between them.
void hippariCheck(Entity *e) {
    Entity *puller1;
    s16 old;
    s16 delta;
    u8 idx2;
    Entity *puller2;
    u8 flags;
    u8 idx1;
    s16 diff;
    Vars_Em0e *vars = VARS(Vars_Em0e, e);
    void *app;
    u8 mode;

    flags = vars->partFlags;
    diff = vars->motiage1->x.HALF.HI - vars->body0->x.HALF.HI;
    idx1 = flags & 3;
    idx2 = (flags & 0x30) >> 4;
    puller1 = playerWork[idx1].entity;
    puller2 = playerWork[idx2].entity;
    app = KnifeApp_getInstance();
    mode = vars->partFlags & 0xcc;
    switch (mode) {
    case 0xc:
        if (diff == 0) {
            old = puller1->x.HALF.HI;
            func_020852f8(puller1, 0x40, 0x18);
            e->x.HALF.HI += (s16)(puller1->x.HALF.HI - old);
            if (vars->unk_70 != 0) {
                vars->unk_70 = 0;
                EnqueueSFX(0x96);
            }
            return;
        }
    case 4:
        if (diff == 0) {
            return;
        }
        playerWork[idx1].specialState = 0;
        puller1->baseDirection = 0x18;
        puller1->unk_42 = em0e_pullStrengthTable[diff >> 2];
        puller1->iframes = -em0e_pullStrengthTable[diff >> 2];
        e->x.HALF.HI = vars->body0->x.HALF.HI;
        if (KnifeApp_isWirelessMode(app) == 0 && mode != 4) {
            puller1->unk_42 = 0;
        }
        if (vars->unk_70 != 0) {
            vars->unk_70 = 0;
            EnqueueSFX(0x96);
        }
        return;
    case 0xc0:
        if (diff == 0) {
            old = puller2->x.HALF.HI;
            func_020852f8(puller2, 0x40, 8);
            e->x.HALF.HI += (s16)(puller2->x.HALF.HI - old);
            if (vars->unk_70 != 0) {
                vars->unk_70 = 0;
                EnqueueSFX(0x96);
            }
            return;
        }
    case 0x40:
        if (diff == 0) {
            return;
        }
        playerWork[idx2].specialState = 0;
        puller2->baseDirection = 8;
        puller2->unk_42 = em0e_pullStrengthTable[diff >> 2];
        puller2->iframes = -em0e_pullStrengthTable[diff >> 2];
        e->x.HALF.HI = vars->motiage1->x.HALF.HI;
        if (KnifeApp_isWirelessMode(app) == 0 && mode != 0x40) {
            puller2->unk_42 = 0;
        }
        if (vars->unk_70 != 0) {
            vars->unk_70 = 0;
            EnqueueSFX(0x96);
        }
        return;
    case 0x44:
        if (diff == 0) {
            return;
        }
        old = vars->body0->x.HALF.HI;
        func_020852f8(vars->body0, 0x20, 8);
        puller1->x.HALF.HI += (s16)(vars->body0->x.HALF.HI - old);
        old = vars->motiage1->x.HALF.HI;
        func_020852f8(vars->motiage1, 0x20, 0x18);
        puller2->x.HALF.HI += (s16)(vars->motiage1->x.HALF.HI - old);
        if (vars->unk_70 != 0) {
            vars->unk_70 = 0;
            EnqueueSFX(0x96);
        }
        return;
    case 0x4c:
        old = puller1->x.HALF.HI;
        func_020852f8(puller1, 0x40, 0x18);
        delta = puller1->x.HALF.HI - old;
        puller2->x.HALF.HI += delta;
        e->x.HALF.HI += delta;
        vars->body0->x.HALF.HI += delta;
        vars->motiage1->x.HALF.HI += delta;
        old = vars->motiage1->x.HALF.HI;
        if (old - vars->body0->x.HALF.HI != 0) {
            func_020852f8(vars->motiage1, 0x20, 0x18);
            puller2->x.HALF.HI += (s16)(vars->motiage1->x.HALF.HI - old);
            e->x.HALF.HI = (vars->motiage1->x.HALF.HI + vars->body0->x.HALF.HI) >> 1;
        }
        if (vars->unk_70 != 0) {
            vars->unk_70 = 0;
            EnqueueSFX(0x96);
        }
        return;
    case 0xc4:
        old = puller2->x.HALF.HI;
        func_020852f8(puller2, 0x40, 8);
        delta = puller2->x.HALF.HI - old;
        puller1->x.HALF.HI += delta;
        e->x.HALF.HI += delta;
        vars->body0->x.HALF.HI += delta;
        vars->motiage1->x.HALF.HI += delta;
        old = vars->body0->x.HALF.HI;
        if (vars->motiage1->x.HALF.HI - old != 0) {
            func_020852f8(vars->body0, 0x20, 8);
            puller1->x.HALF.HI += (s16)(vars->body0->x.HALF.HI - old);
            e->x.HALF.HI = (vars->motiage1->x.HALF.HI + vars->body0->x.HALF.HI) >> 1;
        }
        if (vars->unk_70 != 0) {
            vars->unk_70 = 0;
            EnqueueSFX(0x96);
        }
        return;
    case 0xcc:
        old = puller1->x.HALF.HI;
        func_020852f8(puller1, 0x40, 0x18);
        delta = puller1->x.HALF.HI - old;
        vars->body0->x.HALF.HI += delta;
        old = puller2->x.HALF.HI;
        func_020852f8(puller2, 0x40, 8);
        delta = puller2->x.HALF.HI;
        delta -= old;
        vars->motiage1->x.HALF.HI += delta;
        e->x.HALF.HI = (vars->body0->x.HALF.HI + vars->motiage1->x.HALF.HI) / 2;
        if ((vars->unk_70 & 4) == 0) {
            vars->unk_70 |= 4;
            EnqueueSFX(0x55);
        }
        return;
    default:
        return;
    }
}
