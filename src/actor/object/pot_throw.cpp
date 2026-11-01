#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/pot_throw.h"

// Pot actor, thrown state (module pot). Address -> name:
//   0x0205ef50 pot_throw_throw (original name throw_throw): the thrown pot hits a player that is not in a special state

void pot_throw_throw(Entity *e) {
    if (e->contactFlags & 0x80) {
        if (e->contactedEntity->objKind == 1 && data_0212ceb0[e->contactedEntity->type].statusFlags == 0 &&
            data_0212ceb0[e->contactedEntity->type].specialState == 0 &&
            data_0212ceb0[e->contactedEntity->type].unk_26 == 0) {
            if (KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                u8 playerIndex;

                SetCgColor(0, 0);
                data_0212ceb0[e->contactedEntity->type].statusFlags |= 4;
                e->child = e->contactedEntity;
                e->child->child = e;
                e->action = 4;
                e->z.WORD = 0;
                e->timer = 5;
                e->subtimer = 0;
                InitAnimationForceUpdate(e, 6);

                playerIndex = localPlayerIndex;
                if (!KnifeApp_isWirelessMode(KnifeApp_getInstance())) {
                    playerIndex = *Knife_Single_SinglePlay_GetInstance();
                }
                e->unk_6b = 0;
                if (playerIndex == e->child->type) {
                    pot_ware(e);
                }
                func_0208919c(e->child);
                return;
            }
        }
    }
    e->unk_2e = 4;
    if (e->parent != NULL) {
        e->parent->timer = 2;
    }
}
