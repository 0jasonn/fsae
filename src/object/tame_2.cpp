#include "engine/functions.h"
#include "global.h"

// Tame actor, second unit (module tame). Address -> name (original names from symbols.txt):
//   0x020702c8 tame_move

// Fields of the tame actor beyond the common part of Entity
typedef struct Vars_TameMove {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 moveStep; // offset applied to the position each frame (read as s16 below)
    /* 66 */ u8 unk_66[4];
    /* 6a */ u16 effectCounter; // counts the effects spawned at the end of the timer
} Vars_TameMove;

extern "C" Entity *EffectSet(Entity *e, int kind, int arg);
extern const s8 data_020db580[];
extern const s8 data_020db588[];
extern u8 data_0212ceb4[];
extern u8 data_0212cecb[];
extern u8 data_0212ced1[];
extern u8 data_0212ced8[];
extern u16 frameCounter;

// tame_move, 0x020702c8. Follows the player slot of e->type (stride 0x94): copies its height and its sprite layer,
// then offsets the position from the player by the animation table and runs the timer effects.
ARM void tame_move(Entity *e) {
    Entity *target;
    const s8 *offsets;
    u8 kind;
    s32 step;
    Entity *effect;

    target = *(Entity **)&data_0212ced8[e->type * 0x94];
    if (data_0212ceb4[e->type * 0x94] == 0) {
        PutObjWork(e);
        return;
    }
    e->z.HALF.HI = target->z.HALF.HI;
    if (e->type2 != 0) {
        if (data_0212ced1[e->type * 0x94] >= 0x14) {
            e->spriteSettings.b0 = 1;
            offsets = data_020db588;
            kind = data_0212ced1[e->type * 0x94];
        } else {
            if (data_0212ced1[e->type * 0x94] != 0) {
                e->spriteSettings.b0 = 0;
                return;
            }
            PutObjWork(e);
            return;
        }
    } else {
        if ((data_0212cecb[e->type * 0x94] & 1) != 0) {
            offsets = data_020db580;
            kind = data_0212cecb[e->type * 0x94];
        } else {
            PutObjWork(e);
            return;
        }
    }
    if (kind != 0) {
        UpdateAnimationSingleFrame(e);
        if (e->timer != 0) {
            e->timer--;
            if (e->type2 != 0) {
                step = (0x46 - e->timer) * 10;
                VARS(Vars_TameMove, e)->moveStep = step / 70;
            } else {
                if ((e->timer & 3) == 0) {
                    VARS(Vars_TameMove, e)->moveStep++;
                }
            }
        } else {
            if (e->type2 != 0) {
                VARS(Vars_TameMove, e)->moveStep = 10;
            }
            if (VARS(Vars_TameMove, e)->effectCounter != 0) {
                if ((frameCounter & 0x1f) == 0) {
                    effect = EffectSet(e, 7, 0);
                    if (effect != 0) {
                        effect->layer = e->layer;
                    }
                }
            } else {
                EnqueueSFX(0x1b);
                effect = EffectSet(e, 0x12, 0);
                if (effect != 0) {
                    effect->layer = e->layer;
                }
                VARS(Vars_TameMove, e)->effectCounter++;
            }
        }
        e->spriteSettings.b14 = target->spriteSettings.b14;
        e->x.HALF.HI = target->x.HALF.HI + offsets[e->animationState * 2];
        e->y.HALF.HI = target->y.HALF.HI + offsets[e->animationState * 2 + 1];
        e->layer = target->layer;
        switch (e->animationState) {
        case 0:
            e->y.HALF.HI = e->y.HALF.HI - (s16)VARS(Vars_TameMove, e)->moveStep;
            break;
        case 1:
            e->x.HALF.HI = e->x.HALF.HI + (s16)VARS(Vars_TameMove, e)->moveStep;
            break;
        case 2:
            e->y.HALF.HI = e->y.HALF.HI + (s16)VARS(Vars_TameMove, e)->moveStep;
            break;
        case 3:
            e->x.HALF.HI = e->x.HALF.HI - (s16)VARS(Vars_TameMove, e)->moveStep;
            break;
        }
        if (e->subtimer-- == 0) {
            e->subtimer = 6;
            e->direction = e->direction ^ 0x10;
        }
        MoveDir(e);
        if (e->type2 == 0) {
            if ((data_0212cecb[e->type * 0x94] & 0x40) != 0) {
                e->action++;
            }
        }
    } else {
        PutObjWork(e);
    }
}
