#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/g_callees.h"
#include "object/ido_3.h"

// Ido wait state, third unit (module ido). Address -> name:
//   0x02064f24 ido_wait
//   0x02064fc0 ido_getNextInfo

typedef struct Vars_IdoWait {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 moveCheckMask; // bit i set: player i has to pass ido_yukaPlMoveCheck before the move request
    /* 64 */ u8 unk_64[4];
    /* 68 */ s32 waitTimer; // counts down; ido_getNextInfo runs when it reaches 0
    /* 6c */ u16 *infoStart; // first record of the movement script, read again when the script loops
    /* 70 */ u8 unk_70[4];
    /* 74 */ s16 targetPos; // coordinate the actor moves to along its direction
    /* 76 */ u8 unk_76[2];
    /* 78 */ u16 *nextInfo; // next record of the movement script
} Vars_IdoWait;

ARM void ido_wait(Entity *e) {
    u8 mask;
    u32 playerIndex;

    if (VARS(Vars_IdoWait, e)->waitTimer-- == 0) {
        ido_getNextInfo(e);
    }
    mask = VARS(Vars_IdoWait, e)->moveCheckMask & 0xf;
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
        return;
    }
    if (mask == 0) {
        return;
    }
    for (playerIndex = 0; playerIndex < 2; playerIndex++) {
        if (mask & (1 << playerIndex)) {
            if (ido_yukaPlMoveCheck(&data_0212ceb0[playerIndex]) == 0) {
                mask &= ~(1 << playerIndex);
            }
        }
    }
    Knife_Single_SinglePlay_SetObjMoveReqFlag(Knife_Single_SinglePlay_GetInstance(), e, mask, 0, 0);
}

// Reads the next record of the movement script. A record is four u16 words: a control word (bit 15 = wait record,
// otherwise the low byte is the direction and bits 3-7 the sub action), an operand and a speed (or the speed of
// the no-movement records in the second word).
ARM void ido_getNextInfo(Entity *e) {
    u16 *record;
    u16 *speedRecord;
    s32 target;
    u16 word;
    u16 speed;

    if (*VARS(Vars_IdoWait, e)->nextInfo == 0xffff) {
        if (e->objId == 0x74) {
            e->subAction = 4;
            VARS(Vars_IdoWait, e)->waitTimer = 0xffff;
            return;
        }
        VARS(Vars_IdoWait, e)->nextInfo = VARS(Vars_IdoWait, e)->infoStart;
    }
    record = VARS(Vars_IdoWait, e)->nextInfo;
    word = *record;
    if (word & 0x8000) {
        e->subAction = 4;
        VARS(Vars_IdoWait, e)->waitTimer = record[1];
    } else {
        e->subAction = (word & 0xff) >> 3;
        e->direction = word;
        speedRecord = record + 1;
        switch (e->subAction) {
        case 0:
            target = e->y.HALF.HI - record[1];
            speedRecord = record + 2;
            VARS(Vars_IdoWait, e)->targetPos = target;
            break;
        case 1:
            target = e->x.HALF.HI + record[1];
            speedRecord = record + 2;
            VARS(Vars_IdoWait, e)->targetPos = target;
            break;
        case 2:
            target = e->y.HALF.HI + record[1];
            speedRecord = record + 2;
            VARS(Vars_IdoWait, e)->targetPos = target;
            break;
        case 3:
            target = e->x.HALF.HI - record[1];
            speedRecord = record + 2;
            VARS(Vars_IdoWait, e)->targetPos = target;
            break;
        }
        speed = *speedRecord;
        if (speed != 0) {
            e->speed = speed;
        }
    }
    VARS(Vars_IdoWait, e)->nextInfo += 4;
}
