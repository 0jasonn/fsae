#include "engine/functions.h"
#include "global.h"
#include "actor/object/set53_move2.h"

// set53_move2 (0x020709fc): the boat seat waiting for its riders. It follows the hull while the hull drifts (action 1);
// a rider that boards walks into his seat, a rider facing the wrong way is thrown off, and when both riders are
// seated the hull starts rowing (action 4) and the seat moves to its rowing state.

// Drops the player's hold on the boat (its hull when type2 is set, the seat otherwise)
static inline void set53_releaseHold(Entity *e, Entity *rider) {
    if ((e->type2 != 0 && playerWork[rider->type].holdObject == e->parent) ||
        (e->type2 == 0 && playerWork[rider->type].holdObject == e)) {
        playerWork[rider->type].holdObject = NULL;
    }
}

void set53_move2(Entity *e) {
    Vars_Set53 *v = VARS(Vars_Set53, e);
    Entity *hull = e->parent;
    Entity **riderSlot = &v->rider0;
    u8 *rowFlag = &hull->timer;
    Entity *rider = v->rider0;
    u8 i;
    u8 facing;

    if (hull->action != 1) {
        e->spriteSettings.b0 = 0;
        return;
    }
    e->spriteSettings.b0 = 1;
    e->x.WORD = hull->x.WORD;
    e->y.WORD = hull->y.WORD;
    e->z.WORD = hull->z.WORD;
    e->animationState = hull->animationState;
    if (rider != NULL && v->rider1 != NULL && playerWork[rider->type].unk_02 == 0 &&
        playerWork[v->rider1->type].unk_02 == 0) {
        hull->action = 4;
        e->action++;
        e->subtimer = 1;
        e->timer = 1;
        v->strokeAccel = 0;
        v->strokeTimer = 0;
        playerWork[v->rider1->type].state = 0x13;
        playerWork[v->rider0->type].state = playerWork[v->rider1->type].state;
        return;
    }
    for (i = 0; i < 2; i++) {
        if (rider != NULL) {
            if (playerWork[rider->type].unk_02 != 0) {
                if (playerWork[rider->type].unk_02 & 0x80) {
                    int target = e->x.HALF.HI + data_020db878[e->animationState][i];
                    if (rider->x.HALF.HI != target) {
                        if (rider->x.HALF.HI > target) {
                            rider->x.HALF.HI--;
                        } else {
                            rider->x.HALF.HI++;
                        }
                    }
                    target = e->y.HALF.HI + data_020db888[e->animationState][i];
                    if (rider->y.HALF.HI != target) {
                        if (rider->y.HALF.HI > target) {
                            rider->y.HALF.HI--;
                        } else {
                            rider->y.HALF.HI++;
                        }
                    }
                }
            } else {
                facing = e->animationState;
                if (i == 0) {
                    facing ^= 4;
                }
                if ((playerWork[rider->type].unk_0d & 0x80) || playerWork[rider->type].unk_0d == facing << 2) {
                    rider->x.HALF.HI = e->x.HALF.HI + data_020db878[e->animationState][i];
                    rider->y.HALF.HI = e->y.HALF.HI + data_020db888[e->animationState][i];
                    rider->animationState = facing;
                    playerWork[rider->type].unk_1a = 0x80;
                } else {
                    playerWork[rider->type].unk_02 = 0x81;
                    rider->zVelocity = 0x18000;
                    rider->speed = 0x80;
                    rider->direction = playerWork[rider->type].unk_0d;
                    playerWork[rider->type].statusFlags &= 0xefff;
                    if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                        SinglePlayObject temp;
                        u8 *singlePlay;
                        BOOL constructed;
                        BOOL reset;

                        Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(temp.logList);
                        _Z34Knife_Single_SinglePlay_Initializev(&temp);
                        singlePlay = Knife_Single_SinglePlay_GetInstance();
                        _Z34Knife_Single_SinglePlay_Initializev(&temp);
                        {
                            SinglePlayObject other;
                            constructed = FALSE;
                            reset = FALSE;
                            if (singlePlay[1] != 0) {
                                Knife_Single_SinglePlay_SinglePlayLogList_SinglePlayLogList(other.logList);
                                _Z34Knife_Single_SinglePlay_Initializev(&other);
                                constructed = TRUE;
                                if (rider->type != other.contNo) {
                                    reset = TRUE;
                                }
                            }
                            if (constructed) {
                                _Z34Knife_Single_SinglePlay_Initializev(&other);
                            }
                        }
                        if (reset) {
                            _ZN5Knife6Single10SinglePlay17SinglePlayLogList10InitializeEv(singlePlay + 0x34);
                        }
                    }
                    set53_releaseHold(e, rider);
                    playerWork[rider->type].state = 1;
                    *riderSlot = NULL;
                    *rowFlag = 0xff;
                }
            }
        }
        riderSlot = &v->rider1;
        rider = v->rider1;
        rowFlag = &e->parent->subtimer;
    }
    e->unk_21 = data_020db8cc[e->animationState][1];
}
