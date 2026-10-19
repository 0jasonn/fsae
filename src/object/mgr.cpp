#include "engine/functions.h"
#include "global.h"

// Manager set helpers (module mgr). Address -> name:
//   0x020610b8 getDebu (original name)
//   0x02061114 getMgrInfo (original name)
//   0x02061194 mgrMove (original name)
//   0x02061260 getRandomType (original name)

typedef struct Vars_Mgr {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ u16 waitTimer; // frames to wait before the next command of the script
    /* 72 */ u8 unk_72[2];
    /* 74 */ const u16 *statePtr; // position in the script; points at the next command
    /* 78 */ u8 unk_78[2];
    /* 7a */ u16 counter7a; // counts the scripts started for objId != 0x72
} Vars_Mgr;

extern const u16 data_020d91f4[]; // spawn offsets, pairs of (x, y)
extern const u8 data_020d91d4[]; // random type table, 16 entries
extern const u16 *data_02103814[]; // script entry points, indexed by the function's index
extern const u16 *data_02103834[]; // per-command entry lists, 4 u16 each, terminated by 0xffff
extern const EntityFunc data_02115a4c[]; // indexed by e->action

void mgrMove(Entity *e);
u8 getRandomType(void);

ARM void getDebu(Entity *e) {
    Entity *enemy;
    u8 index;

    enemy = GetEnemyWork(0x31);
    if (enemy == NULL) {
        return;
    }
    enemy->type = getRandomType();
    index = Random() & 0x3e;
    enemy->x.HALF.HI = data_020d91f4[index];
    enemy->y.HALF.HI = data_020d91f4[index + 1];
    enemy->direction = 0xff;
    enemy->layer = 0x4000;
}

ARM void getMgrInfo(Entity *e) {
    u32 index;

    if (e->objId == 0x72) {
        index = Random() % 7;
    } else {
        VARS(Vars_Mgr, e)->counter7a++;
        if (VARS(Vars_Mgr, e)->counter7a >= 4) {
            VARS(Vars_Mgr, e)->counter7a = 0;
            index = 7;
        } else {
            index = Random() % 7;
        }
    }
    VARS(Vars_Mgr, e)->statePtr = data_02103814[index];
    mgrMove(e);
}

ARM void mgrMove(Entity *e) {
    const u16 *cmd;
    const u16 *list;
    Entity *enemy;

    if (VARS(Vars_Mgr, e)->waitTimer != 0) {
        VARS(Vars_Mgr, e)->waitTimer--;
        return;
    }
    cmd = VARS(Vars_Mgr, e)->statePtr;
    if (cmd[0] == 0xffff) {
        return;
    }
    if (cmd[0] & 0x8000) {
        VARS(Vars_Mgr, e)->waitTimer = cmd[0] & 0x7fff;
    } else {
        list = data_02103834[cmd[0]];
        if (list[0] != 0xffff) {
            do {
                enemy = GetEnemyWork(0x31);
                if (enemy != NULL) {
                    enemy->type = list[0] >> 8;
                    enemy->direction = list[0];
                    enemy->type2 = list[1];
                    enemy->x.HALF.HI = list[2];
                    enemy->y.HALF.HI = list[3];
                    if (enemy->type >= 4) {
                        enemy->type = getRandomType();
                    }
                }
                list += 4;
            } while (list[0] != 0xffff);
        }
    }
    VARS(Vars_Mgr, e)->statePtr = cmd + 1;
}

ARM u8 getRandomType(void) {
    return data_020d91d4[Random() & 0xf];
}
