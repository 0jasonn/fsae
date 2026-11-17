#include "engine/functions.h"
#include "actor/enemy/em26.h"
#include "engine/player.h"

// em28_damage, 0x02040ff8. A hit by a player below index 3 remembers that player's entity (the local one in a
// single player game) before the common knockback runs.
void em28_damage(Entity *e) {
    if (e->contactedEntity->type < 3) {
        if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0) {
            V(e)->unk_64 = playerWork[*Knife_Single_SinglePlay_GetInstance()].entity;
        } else {
            V(e)->unk_64 = playerWork[e->contactedEntity->type].entity;
        }
    }
    GenericKnockback(e, em27_handlerTable);
}
