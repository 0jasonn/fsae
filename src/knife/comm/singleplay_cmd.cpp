#include "knife/comm/singleplay_a.h"

// Knife::Single::SinglePlay::CheckCommand(PL_WORK_*, PL_WORK_*) (0x02099864): decides whether the pending request
// (reqKind 1: controller change, 2: formation change) may run now. The first player is the controlled one.
BOOL Knife_Single_SinglePlay_CheckCommand(void *self, PlayerData *player0, PlayerData *player1) {
    SinglePlayWork *work = (SinglePlayWork *)self;
    Entity *contEntity;
    Entity *otherEntity;
    int contDead;
    int otherDead;
    PlayerData *swapPlayer;
    u8 reqNo;
    u8 want;

    if (work->reqKind == 0) {
        return FALSE;
    }
    if (work->contNo != 0) {
        swapPlayer = player0;
        otherEntity = player0->entity;
        contEntity = player1->entity;
        player0 = player1;
        player1 = swapPlayer;
    } else {
        contEntity = player0->entity;
        otherEntity = player1->entity;
    }
    switch (work->reqKind) {
    case 1:
        if ((player0->statusFlags & 0x1000) && (player1->statusFlags & 0x1000) &&
            *(u32 *)&player0->unk_8c[4] == *(u32 *)&player1->unk_8c[4]) {
            if (work->contChanging != 0) {
                return FALSE;
            }
        }
        if (player0->unk_02 != 0 || player1->unk_02 != 0 || contEntity->action == 0xf ||
            otherEntity->action == 0xf) {
            return FALSE;
        }
        if (contEntity->action == 2 || otherEntity->action == 2 || work->unk_10[0] == 2 || work->unk_10[1] == 2) {
            return FALSE;
        }
        if (contEntity->action == 3 || otherEntity->action == 3 || contEntity->action == 0x11 || otherEntity->action == 0x11 || contEntity->action == 0x12 ||
            otherEntity->action == 0x12) {
            return FALSE;
        }
        if (((player0->unk_12 == 4 || player0->unk_12 == 0x94 || player0->unk_12 == 0xa0) && player0->unk_14 == 0 &&
             contEntity->action != 0xa) ||
            ((player1->unk_12 == 4 || player1->unk_12 == 0x94 || player1->unk_12 == 0xa0) && player1->unk_14 == 0 &&
             otherEntity->action != 0xa)) {
            return FALSE;
        }
        contDead = 1;
        if (contEntity->action != 0xa && contEntity->health != 0) contDead = 0;
        otherDead = 1;
        if (otherEntity->action != 0xa && otherEntity->health != 0) otherDead = 0;
        if (contDead || otherDead) {
            want = work->reqNo;
            if (want == 0xff) {
                want = (work->contNo + 1) & 1;
            }
            want ^= work->contNo;
            if (want == work->contNo && contDead && otherDead) {
                if (work->contChanging == 0) {
                    return TRUE;
                }
            }
            if ((want == 0 && contDead) || (want == 1 && otherDead)) {
                return FALSE;
            }
            if ((work->contNo == 0 && contEntity->action != 0xa && contEntity->health == 0) ||
                (work->contNo == 1 && otherEntity->action != 0xa && otherEntity->health == 0)) {
                return FALSE;
            }
            if (contDead && otherDead) {
                return FALSE;
            }
        }
        if ((player0->hitFlags & 0xa0) || (player1->hitFlags & 0xa0) || contEntity->action == 6 || otherEntity->action == 6) {
            return FALSE;
        }
        break;
    case 2:
        reqNo = work->reqNo;
        if (reqNo != 0xff && (player0->statusFlags & 0x1000) && (player1->statusFlags & 0x1000) &&
            *(u32 *)&player0->unk_8c[4] == *(u32 *)&player1->unk_8c[4]) {
            return FALSE;
        }
        if (player0->motionId == 0x22c && player1->motionId == 0x22c) {
            return FALSE;
        }
        if (player0->unk_02 != 0 || player1->unk_02 != 0 || contEntity->action == 0xf ||
            otherEntity->action == 0xf) {
            return FALSE;
        }
        if (reqNo == 0 && !(contEntity->action == 0xa && otherEntity->action == 0xa)) {
            return TRUE;
        }
        if ((player0->statusFlags & 0xf11) || (player1->statusFlags & 0xf11)) {
            return FALSE;
        }
        if (reqNo != 0xff && (player0->statusFlags & 0x1000) && (player1->statusFlags & 0x1000) &&
            *(u32 *)&player0->unk_8c[4] == *(u32 *)&player1->unk_8c[4]) {
            return FALSE;
        }
        if ((player0->unk_07 & 0x80) && (player1->unk_07 & 0x80)) {
            return FALSE;
        }
        if (player0->motionId == 0x2c1 || player1->motionId == 0x2c1) {
            return FALSE;
        }
        if (contEntity->action == 2 || otherEntity->action == 2 || work->unk_10[0] == 2 || work->unk_10[1] == 2) {
            return FALSE;
        }
        if (contEntity->action == 3 || otherEntity->action == 3 || contEntity->action == 0x11 || otherEntity->action == 0x11 || contEntity->action == 0x12 ||
            otherEntity->action == 0x12) {
            return FALSE;
        }
        if (((player0->unk_12 == 4 || player0->unk_12 == 0x94 || player0->unk_12 == 0xa0) && player0->unk_14 == 0 &&
             contEntity->action != 0xa) ||
            ((player1->unk_12 == 4 || player1->unk_12 == 0x94 || player1->unk_12 == 0xa0) && player1->unk_14 == 0 &&
             otherEntity->action != 0xa)) {
            return FALSE;
        }
        if (contEntity->action == 0xa || otherEntity->action == 0xa) {
            return FALSE;
        }
        if (player1->specialState != 0) {
            return FALSE;
        }
        if ((player0->hitFlags & 0xa0) || (player1->hitFlags & 0xa0) || contEntity->action == 6 || otherEntity->action == 6) {
            return FALSE;
        }
        break;
    }
    return TRUE;
}
