#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/objdecls_f.h"

// Set51 actor (module set51). Address -> name:
//   0x0205ad24 Set51 (original name), dispatches on e->type through set51_typeHandlers
//   0x0205ad40 set51_parent (original name)
//   0x0205adcc set51_child (original name), dispatches on e->action through set51_childActions
//   set51_init at 0x0205ade8 is in scratch/agentF/nonmatching/set51_init.c
//   0x0205ae5c set51_move (original name)

extern const EntityFunc set51_typeHandlers[]; // set51_typeHandlers, indexed by e->type
extern const EntityFunc set51_childActions[]; // set51_childActions, indexed by e->action
extern const s8 data_020d8a34[];              // vertical offset table, indexed by subtimer & 7
extern u16 data_0212c594;

void set51_move(Entity *e);

void Set51(Entity *e) {
    set51_typeHandlers[e->type](e);
}

void set51_parent(Entity *e) {
    u8 i;
    Entity *child;

    e->action++;
    CalcRanking();
    for (i = 0; i < gameState.playerCount; i++) {
        child = GetSetWork(0x51, 1, ranking_getKey(i));
        if (child != NULL) {
            child->contactedEntity = playerWork[i].entity;
        }
    }
    PutObjWork(e);
}

void set51_child(Entity *e) {
    set51_childActions[e->action](e);
}

// Set51 actor, init (module set51). Address -> name:
//   0x0205ade8 set51_init (original name)

void set51_move(Entity *e); // 0x0205ae5c

void set51_init(Entity *e) {
    e->action++;
    e->spriteSettings.b14 = 0;
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = 0;
    e->spriteSettings.b16 = (e->contactedEntity->type + 7) & 0xf;
    e->timer = (4 - e->type2) * 0x14;
    InitAnimationForceUpdate(e, e->type2);
    set51_move(e);
}

// Set51 actor, second unit (module set51). Address -> name:
//   0x0205ae5c set51_move (original name)

extern const s8 data_020d8a34[]; // vertical offset table, indexed by subtimer & 7

void set51_move(Entity *e) {
    Entity *contact;

    if (e->timer == 0) {
        e->spriteSettings.b0 = 1;
        contact = e->contactedEntity;
        e->x.HALF.HI = contact->x.HALF.HI;
        e->y.HALF.HI = contact->y.HALF.HI;
        e->z.HALF.HI = contact->z.HALF.HI + data_020d8a34[e->subtimer & 7];
        if ((data_0212c594 & 1) != 0) {
            e->subtimer++;
        }
    } else {
        e->timer--;
    }
}
