#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "actor/object/set66.h"

// 0x0207553c plStCheck (original name): nonzero while the player cannot be hit or is busy (status flags 0x201,
// state byte, call state, no health, or its entity in action 2 or 3).

int plStCheck(PlayerData *player) {
    Entity *e;
    if (player->statusFlags & 0x201) {
        return TRUE;
    }
    if (player->unk_02 != 0) {
        return TRUE;
    }
    if (player->callState != 0 || player->entity->health == 0) {
        return TRUE;
    }
    e = player->entity;
    return (u8)(e->action + 0xfe) <= 1;
}
