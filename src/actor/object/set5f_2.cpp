#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/setmisc.h"
#include "actor/object/set5f.h"

// Set5f actor, second unit (module set5f). Address -> name:
//   0x020605bc type0_kudake, 0x02060670 type0_plBackJump
//   0x020607c4 set5f_type1, 0x02060864 set5f_type2, 0x020608cc set5f_plset (original names)

extern const s8 data_020d90ac[];
extern const s8 data_020d90c0[];
extern Entity *mapState;

void set5f_plset(Entity *e);

void type0_kudake(Entity *e) {
    Entity *target;

    if (e->timer == 0) {
        e->action = 8;
        e->timer = 8;
        return;
    }
    e->timer--;
    if (e->timer >= 0x79) {
        return;
    }
    if (e->timer & 1) {
        e->child->x.HALF.HI += data_020d90ac[(e->timer & 6) >> 1];
    }
    if (e->timer & 7) {
        return;
    }
    target = GetSetWork(0xf, 0xf, 0);
    if (target == NULL) {
        return;
    }
    ObjPosCopyOfs32(e, target, data_020d90c0[e->timer >> 2] << 16, data_020d90c0[(e->timer >> 2) + 1] << 16);
}

void type0_plBackJump(Entity *e) {
    u8 i;
    u8 direction;
    Entity *tama;
    Entity *enemy;
    u8 enemyId;

    if (e->timer != 0) {
        e->timer--;
        return;
    }
    direction = 2;
    for (i = 0; i < 8; direction += 4, i++) {
        tama = GetTamaWork(0xb);
        if (tama != NULL) {
            ObjPosCopy(e, tama);
            tama->type = 1;
            tama->timer = 1;
            tama->direction = direction;
            tama->layer = 0x8000;
        }
    }
    for (i = 0; i < gameState.playerCount; i++) {
        playerWork[i].state = 0xf;
        playerWork[i].stateTimer = 0xb4;
        playerWork[i].motionId = 0xc;
        playerWork[i].unk_02 = 0x41;
        playerWork[i].entity->direction = 0x10;
        playerWork[i].entity->animationState = 0;
        playerWork[i].entity->zVelocity = 0x18000;
    }
    enemyId = 0xf;
    enemy = GetEnemyWork(enemyId);
    if (enemy == NULL) {
        return;
    }
    ObjPosCopy(e, enemy);
    mapState = enemy;
    e->child->health = 0;
    FadeSet(2, 0x10);
    SoundReq(0x208 - enemyId);
    SoundReq(0xd);
    PutObjWork(e);
}

void set5f_type1(Entity *e) {
    Entity *child;

    if (e->action != 0) {
        if (e->health != 0) {
            return;
        }
        e->child->health = 0;
        PutObjWork(e);
    } else {
        child = GetSetWork(0x5f, 2, 0);
        if (child == NULL) {
            return;
        }
        ObjPosCopy(e, child);
        child->parent = e;
        e->child = child;
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->health = 1;
        e->unk_5e.b0 = 2;
        InitAnimationForceUpdate(e, 0);
    }
}

void set5f_type2(Entity *e) {
    if (e->action != 0) {
        ObjPosCopy(e->parent, e);
        if (e->health != 0) {
            return;
        }
        PutObjWork(e);
    } else {
        e->action = 1;
        e->spriteSettings.b0 = 1;
        e->health = 1;
        e->unk_5e.b0 = 0;
        InitAnimationForceUpdate(e, 1);
    }
}

#define SET5F_PLAYER_POS(i, px, py)                              \
    playerWork[i].entity->x.WORD = (px);                      \
    playerWork[i].entity->y.WORD = (py);                      \
    playerWork[i].entity->z.WORD = 0;                         \
    playerWork[i].entity->animationState = 0;

void set5f_plset(Entity *e) {
    switch (gameState.playerCount) {
    case 2:
        SET5F_PLAYER_POS(0, 0x1e80000, 0x2780000);
        SET5F_PLAYER_POS(1, 0x2080000, 0x2780000);
        break;
    case 3:
        SET5F_PLAYER_POS(0, 0x1e80000, 0x2780000);
        SET5F_PLAYER_POS(1, 0x1f80000, 0x2780000);
        SET5F_PLAYER_POS(2, 0x2080000, 0x2780000);
        break;
    case 4:
        SET5F_PLAYER_POS(0, 0x1e00000, 0x2780000);
        SET5F_PLAYER_POS(1, 0x1f00000, 0x2780000);
        SET5F_PLAYER_POS(2, 0x2000000, 0x2780000);
        SET5F_PLAYER_POS(3, 0x2100000, 0x2780000);
        break;
    }
}
