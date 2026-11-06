#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/objdecls.h"
#include "engine/entity.h"
#include "actor/object/set57.h"

// Kenfuri end, union and Set57 actor (provisional module kenfuri). Address -> name:
//   0x0207303c kenfuri_start (original name)
//   0x02073094 link_union (original name)
//   0x020730b0 union_init, 0x020730e0 union_move, 0x0207318c union_wait (original names)
//   0x020731d4 Set57 (original name); set57_init (0x020731f0) is in scratch/agentD/nonmatching

extern s32 data_02134924; // game flag word
extern s32 em12_typeMasks; // game flag word
extern const u16 union_moveBounds[]; // ObjAnimMoveSet bounds (union_moveBounds)
extern const EntityFunc union_subActions[]; // indexed by e->subAction (union_subActions)


void kenfuri_start(Entity *e) {
    func_02085934(e, e->unk_1b);
    MoveDir(e);
    if (e->timer != 0) {
        e->timer--;
        if (e->timer == 0) {
            e->animationState = 4;
            e->direction = 0x10;
        }
    }
    if (e->y.HALF.HI > 0x13c) {
        PutObjWork(e);
    }
}

void link_union(Entity *e) {
    union_subActions[e->subAction](e);
}

void union_init(Entity *e) {
    ObjAnimMoveSet(e, union_moveBounds, 0x78);
    e->timer = 0x78;
    e->subAction++;
}

void union_move(Entity *e) {
    e->spriteSettings.b0 = 1;
    ObjAnimMoveLine(e);
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    e->subAction++;
    e->timer = 0x3c;
    if (e->type == 0) {
        e->spriteSettings.b0 = 1;
        e->spriteSettings.b16 = (gameState.unk_50[3] + 7) & 0xf;
        e->spriteSettings.b20 = e->spriteSettings.b16;
        SoundReq(0x208);
    } else {
        PutObjWork(e);
    }
}

void union_wait(Entity *e) {
    e->timer--;
    if (e->timer != 0) {
        return;
    }
    em12_typeMasks |= 8;
    playerWork[e->type].state = 2;
}

void Set57(Entity *e) {
    set57_actions[e->action](e);
}
