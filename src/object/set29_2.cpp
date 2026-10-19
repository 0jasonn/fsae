#include "engine/functions.h"
#include "object/set29.h"
#include "global.h"

ARM void set29_move(Entity *e) {
    UpdateAnimationSingleFrame(e);
    if (e->frame & 0x80) {
        InitAnimationForceUpdate(e, 0);
        e->unk_28 = (Random() & 0xf0) + 1;
    }
    if (*VARS(Vars_Set29, e)->cellPtr == VARS(Vars_Set29, e)->cellValue) {
        return;
    }
    PutObjWork(e);
}

ARM BOOL test(Entity *e, u16 a, u16 b) {
    Entity *enemy;
    if ((Random() & 0x3f) < 2) {
        enemy = GetEnemyWork(9);
        if (enemy != NULL) {
            ObjPosCopy(e, enemy);
            enemy->type = e->type;
            if (b <= 0x24) {
                RewCellOne(0x4f, a, 0x4000);
            } else {
                RewCellOne(0x78, a, 0x8000);
            }
        }
        return TRUE;
    }
    return FALSE;
}
