#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/enemy/em21.h"
#include "actor/enemy/em21_2.h"

// Returns the direction (0x80 | direction) in which the target is crossing within reach of e, or the wait-timer result.
u8 em21_crossCheck(Entity *e) {
    s32 idx;
    Entity *target;
    s32 dx;
    s32 ex, tx;
    s32 dy;
    u8 result;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) != 0) {
        idx = frameCounter.frame & 3;
    } else {
        idx = *Knife_Single_SinglePlay_GetInstance();
    }
    target = playerWork[idx].entity;
    if (target != NULL) {
        if (playerWork[target->type].unk_26 == 0) {
            return 0;
        }
        ex = e->x.HALF.HI;
        tx = target->x.HALF.HI;
        dx = tx - ex;
        if ((u16)(dx + 0x12) <= 0x24) {
            dy = target->y.HALF.HI - e->y.HALF.HI;
            if ((u16)(dy + 0x40) <= 0x80) {
                result = 0x80;
                if (e->y.HALF.HI <= target->y.HALF.HI) {
                    result = 0x90;
                }
                return result;
            }
        }
        if ((u16)(dx + 0x40) <= 0x80) {
            dy = target->y.HALF.HI - e->y.HALF.HI;
            if ((u16)(dy + 0x12) <= 0x24) {
                result = 0x98;
                if (ex <= tx) {
                    result = 0x88;
                }
                return result;
            }
        }
    }
    VARS(Vars_em21, e)->waitTimer--;
    if (VARS(Vars_em21, e)->waitTimer != 0) {
        return 0;
    }
    return (e->direction & 0x18) | 0x80;
}
