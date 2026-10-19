#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "object/objdecls.h"

// Set56 actor and its link helpers (module set56). Address -> name:
//   0x02072608 Set56 (original name)
//   0x02072638 knife_event_check (original name event_check)
//   0x02072684 link_disp (original name) is in scratch/agentD/nonmatching (near miss)

extern const EntityFunc data_02116500[]; // indexed by e->action

void knife_event_check(Entity *e);
void link_disp(Entity *e);

ARM void Set56(Entity *e) {
    knife_event_check(e);
    data_02116500[e->action](e);
    link_disp(e);
}

// Copies the pending state of the player that owns this entity (PlayerData indexed by e->type) into the entity
ARM void knife_event_check(Entity *e) {
    PlayerData *pl;

    pl = &data_0212ceb0[e->type];
    if (e->action == 0 || pl->state == 0) {
        return;
    }
    e->action = pl->state;
    e->subAction = 0;
    e->timer = pl->stateTimer;
    e->subtimer = pl->unk_39;
    pl->state = 0;
}
