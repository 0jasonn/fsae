#include "engine/functions.h"
#include "engine/player.h"
#include "actor/enemy/gieni.h"

// gieniGetAimPl (0x02030108): picks a random player slot and walks the slots in a random direction until it finds a
// connected, unhidden player with a live entity. Falls back to the entity of slot 0.
Entity *gieniGetAimPl(void) {
    s8 slot = (s8)(Random() % gameState.playerCount);
    s8 step = (Random() & 1) ? 1 : -1;
    s8 tried;

    for (tried = 0; tried < gameState.playerCount; tried++) {
        PlayerData *player = &playerWork[slot];
        if (!(playerKeysPrev[slot] & 0x1000) && player->unk_26 == 0 && !(player->statusFlags & 0xc80) &&
            player->entity != NULL && player->entity->health != 0) {
            return player->entity;
        }
        slot = slot + step;
        if (slot == gameState.playerCount) {
            slot = 0;
        }
        if (slot == -1) {
            slot = gameState.playerCount;
        }
    }
    return playerWork[0].entity;
}
