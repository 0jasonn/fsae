#include "engine/functions.h"
#include "engine/player.h"
#include "ui/stagesel_common.h"
#include "global.h"

extern const EntityFunc data_020dccfc[]; // action table of the tama05 family

// Tama05 (0x0207e76c): a contact with bit 7 set removes the actor; when the toucher is a player with status bit 0x80
// (or a type 3 actor with a different contact value) the actor first moves a hit effect onto itself. Otherwise the
// action runs, and the actor is removed once its parent has no health left.
extern "C" {
void Tama05(Entity *e);
}

void Tama05(Entity *e) {
    if (e->contactFlags & 0x80) {
        if ((e->type == 3 && e->contactFlags != 0x80) ||
            (e->contactedEntity != NULL && e->contactedEntity->objKind == 1 &&
             (playerWork[e->contactedEntity->type].statusFlags & 0x80))) {
            Entity *effect = GetSetWork(0xf, 0xd, 0);
            if (effect != NULL) {
                ObjPosCopy(e, effect);
            }
        }
        PutObjWork(e);
        return;
    }
    if (e->parent == NULL || e->parent->health != 0) {
        data_020dccfc[e->action](e);
    } else {
        PutObjWork(e);
    }
}
