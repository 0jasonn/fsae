#include "engine/functions.h"
#include "global.h"
#include "actor/object/fdecls.h"

// Bar master and bar slave actors (module barmaster). Address -> name:
//   0x0205bd60 barMaster (original name), dispatches on e->action through barMaster_actions
//   0x0205bd7c barMaster_init, 0x0205bdc8 barMaster_wait, 0x0205be6c barMaster_move
//   0x0205bee8 namelPosSync, 0x0205bf34 barSlave, 0x0205bfe8 slavePosSync

extern const EntityFunc barMaster_actions[]; // barMaster_actions, indexed by e->action
#include "engine/effect_state.h"

void namelPosSync(Entity *e);
void slavePosSync(Entity *e);

void barMaster(Entity *e) {
    barMaster_actions[e->action](e);
}

void barMaster_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b30 = 3;
    e->spriteSettings.b14 = 3;
    e->unk_5e.b0 = 1;
    e->subtimer = 0;
    e->unk_21 = 0x11;
    namelPosSync(e);
}

void barMaster_wait(Entity *e) {
    Entity *child;
    Entity *second;

    effectState.panelShown = 1;
    namelPosSync(e);
    if (e->subAction == 0) {
        return;
    }
    e->spriteSettings.b0 = 2;
    e->action++;
    child = GetSetWork(0x3b, 4, e->type2);
    e->child = child;
    if (child == NULL) {
        return;
    }
    child->parent = e;
    e->child->child = e->parent;
    second = GetSetWork(0x3b, 4, e->type2);
    if (second != NULL) {
        second->parent = e->child;
        second->child = e->parent;
        second->unk_16 = 1;
    }
}

void barMaster_move(Entity *e) {
    if (e->subtimer < 0x88) {
        e->subtimer += 8;
        effectState.panelShown = 1;
    }
    namelPosSync(e);
    e->spriteSettings.b0 = ((effectState.panelState & 3) == e->type2) ? 0 : 2;
    if (effectState.panelPhase == 3) {
        PutObjWork(e);
    }
}

void namelPosSync(Entity *e) {
    if (e->parent == NULL) {
        e->y.HALF.HI = 0xd0;
        return;
    }
    ObjPosCopy(e->parent, e);
    e->x.HALF.HI += e->subtimer + 0x10;
    e->y.HALF.HI += 0x14;
}

void barSlave(Entity *e) {
    if (e->action == 0) {
        e->action = 1;
        e->spriteSettings.b30 = 3;
        e->spriteSettings.b0 = 2;
        e->spriteSettings.b14 = 3;
        e->unk_5e.b0 = 0;
        e->unk_21 = (e->unk_16 != 0) ? 0xf : 0x10;
    }
    slavePosSync(e);
    e->spriteSettings.b0 = ((effectState.panelState & 3) == e->type2) ? 0 : 2;
    if (effectState.panelPhase == 3) {
        PutObjWork(e);
    }
}

void slavePosSync(Entity *e) {
    if (e->parent == NULL || e->child == NULL) {
        e->y.HALF.HI = 0xd0;
        return;
    }
    ObjPosCopy(e->parent, e);
    e->x.HALF.HI -= 0x30;
    if (e->child->x.HALF.HI + 0x10 > e->x.HALF.HI) {
        e->x.HALF.HI = e->child->x.HALF.HI + 0x10;
    }
}
