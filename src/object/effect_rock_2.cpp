#include "engine/functions.h"
#include "global.h"
#include "object/effectdecls.h"

// effect_rock_move (0x0206e688), original name effect_rock_move(OBJ_WORK_*). Module effect_rock.
// effectPhaseTable[type2] counts the frames of the rock, the position of the object follows it.

ARM void effect_rock_move(Entity *e) {
    s32 phase;

    e->unk_1b = 0xb1;
    e->spriteSettings.b20 = 7;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    switch (e->type2) {
    case 0:
        phase = effectPhaseTable[e->type2] + 1;
        effectPhaseTable[e->type2] = phase;
        e->x.HALF.HI = 0xe4 - phase / 2;
        e->y.HALF.HI = 0x4e + (effectPhaseTable[e->type2] * effectPhaseTable[e->type2]) / 20;
        if (effectPhaseTable[e->type2] > 20) {
            PutObjWork(e);
        }
        break;
    case 1:
        phase = effectPhaseTable[e->type2] + 1;
        effectPhaseTable[e->type2] = phase;
        e->x.HALF.HI = 0xee + phase / 2;
        e->y.HALF.HI = 0x52 + (effectPhaseTable[e->type2] * effectPhaseTable[e->type2]) / 10;
        if (effectPhaseTable[e->type2] > 15) {
            PutObjWork(e);
        }
        break;
    case 2:
        phase = effectPhaseTable[e->type2] + 1;
        effectPhaseTable[e->type2] = phase;
        e->x.HALF.HI = 0xea + phase / 3;
        e->y.HALF.HI = 0x4a + (effectPhaseTable[e->type2] * effectPhaseTable[e->type2]) / 30;
        if (effectPhaseTable[e->type2] > 20) {
            PutObjWork(e);
        }
        break;
    case 3:
        phase = effectPhaseTable[e->type2] + 1;
        effectPhaseTable[e->type2] = phase;
        e->x.HALF.HI = 0xe0 - phase / 3;
        e->y.HALF.HI = 0x4c + (effectPhaseTable[e->type2] * effectPhaseTable[e->type2]) / 30;
        if (effectPhaseTable[e->type2] > 15) {
            PutObjWork(e);
        }
        break;
    case 7:
        effectPhaseTable[e->type2] = effectPhaseTable[e->type2] + 1;
        if (effectPhaseTable[e->type2] > 0x5a) {
            PutObjWork(e);
        }
        return;
    default:
        break;
    }
    e->spriteSettings.b0 = 1;
    UpdateAnimationSingleFrame(e);
}
