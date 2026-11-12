#include "engine/player.h"
#include "engine/functions.h"
#include "global.h"
#include "actor/object/set53_row.h"

// set53_row (0x02070dd0): the rowing state of the boat seat.

// Drops the player's hold on the boat (its hull when type2 is set, the seat otherwise)
static inline void set53_releaseHold(Entity *e, Entity *rider) {
    if ((e->type2 != 0 && playerWork[rider->type].holdObject == e->parent) ||
        (e->type2 == 0 && playerWork[rider->type].holdObject == e)) {
        playerWork[rider->type].holdObject = NULL;
    }
}

// Puts a rider off the boat onto the cell grid of the hull
static inline void set53_dropRider(Entity *e, Entity *rider) {
    playerWork[rider->type].statusFlags &= 0xefff;
    set53_releaseHold(e, rider);
    if (rider->action == 10) {
        func_0208a954(rider);
    } else {
        rider->x.HALF.HI = (e->parent->x.HALF.HI & 0xfff0) | 8;
        rider->y.HALF.HI = (e->parent->y.HALF.HI & 0xfff0) | 8;
    }
}

// Throws a rider off the boat
static inline void set53_throwRider(Entity *e, Entity *rider, u8 index) {
    playerWork[rider->type].unk_02 = 0x81;
    rider->zVelocity = 0x18000;
    rider->speed = 0x80;
    rider->direction = set53_scrcheck(e, rider, index);
    playerWork[rider->type].statusFlags &= 0xefff;
    playerWork[rider->type].state = 1;
    set53_releaseHold(e, rider);
}

// While the hull rows (action 4) the riders sit at their oars and A starts a stroke for the rider whose turn it is;
// when the hull lands (5) the riders step off, otherwise they are thrown off.
void set53_row(Entity *e) {
    Vars_Set53 *v = VARS(Vars_Set53, e);
    Entity *hull = e->parent;
    Entity *rider = v->rider0;
    u8 i;
    u8 *rowFlag;
    u8 facing;

    if (hull->action != 4) {
        if (hull->action == 5) {
            set53_dropRider(e, rider);
            set53_dropRider(e, v->rider1);
        } else {
            set53_throwRider(e, rider, 0);
            set53_throwRider(e, v->rider1, 1);
        }
        v->rider1 = NULL;
        v->rider0 = NULL;
        e->action = 2;
        set53_move2(e);
    } else {
        e->x.WORD = hull->x.WORD;
        e->y.WORD = hull->y.WORD;
        e->y.HALF.HI += hull->z.HALF.HI;
        e->animationState = hull->animationState;
        rowFlag = &e->timer;
        for (i = 0; i < 2; i++) {
            rider->x.HALF.HI = e->x.HALF.HI + data_020db878[e->animationState][i];
            rider->y.HALF.HI = e->y.HALF.HI + data_020db888[e->animationState][i];
            facing = e->animationState;
            if (i == 0) {
                facing ^= 4;
            }
            if (playerWork[rider->type].unk_02 == 0 && rider->action == 0x13) {
                if ((playerWork[rider->type].unk_0d & 0x80) || playerWork[rider->type].unk_0d == facing << 2) {
                    rider->animationState = facing;
                    playerWork[rider->type].unk_1a = 0x80;
                    playerWork[rider->type].motionId = *rowFlag + data_020db898[rider->animationState];
                    rider->unk_5e.b0 = 3;
                } else {
                    rider->unk_5e.b0 = 2;
                }
            }
            rowFlag = &e->subtimer;
            rider = v->rider1;
        }
        if (e->timer != 0) {
            if (playerWork[v->rider0->type].unk_1a == 0x80 && (playerKeys[v->rider0->type] & 1)) {
                e->timer = 0;
                e->subtimer = 1;
                v->strokeAccel = 0x10;
                v->strokeTimer = 8;
                EnqueueSFX(0x97);
            }
        } else if (e->subtimer != 0) {
            if (playerWork[rider->type].unk_1a == 0x80 && (playerKeys[rider->type] & 1)) {
                e->timer = 1;
                e->subtimer = 0;
                v->strokeAccel = 0x10;
                v->strokeTimer = 8;
                EnqueueSFX(0x97);
            }
        }
        e->unk_21 = data_020db8cc[e->animationState][e->timer | (e->subtimer << 2)];
        e->unk_2f = e->parent->unk_2f;
        if (v->strokeTimer == 0) {
            return;
        }
        if (--v->strokeTimer == 0) {
            rowFlag = &e->timer;
            if (e->timer == 0) {
                rowFlag = &e->subtimer;
            }
            if (*rowFlag == 1) {
                *rowFlag = 2;
                v->strokeTimer = 0xf;
                v->strokeAccel = 0x80;
            }
        } else {
            VARS(Vars_Set53Hull, e->parent)->speed += v->strokeAccel;
            if (VARS(Vars_Set53Hull, e->parent)->speed > 0x200) {
                VARS(Vars_Set53Hull, e->parent)->speed = 0x200;
            }
        }
    }
}
