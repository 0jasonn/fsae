#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls_f.h"

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

ARM void Set51(Entity *e) {
    set51_typeHandlers[e->type](e);
}

ARM void set51_parent(Entity *e) {
    u8 i;
    Entity *child;

    e->action++;
    CalcRanking();
    for (i = 0; i < data_0212c7c8.unk_0; i++) {
        child = GetSetWork(0x51, 1, ranking_getKey(i));
        if (child != NULL) {
            child->contactedEntity = data_0212ceb0[i].entity;
        }
    }
    PutObjWork(e);
}

ARM void set51_child(Entity *e) {
    set51_childActions[e->action](e);
}
