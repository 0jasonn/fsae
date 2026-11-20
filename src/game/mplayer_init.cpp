#include "engine/functions.h"
#include "engine/player.h"
#include "game/frame_load.h"

// MPlayerInit(unsigned char, unsigned char, unsigned char) (0x0204c87c): creates the map-screen marker object of a player at
// the given map cell and registers it as the player's entity.
void MPlayerInit(u8 player, u8 cellX, u8 cellY) {
    Entity *marker = GetObjWork();
    if (marker == NULL) {
        return;
    }
    marker->objKind = 1;
    marker->objId = 0;
    marker->type = player;
    marker->spriteSettings.b30 = 2;
    marker->unk_20 = player << 5;
    marker->statusFlags = 0x80 | player;
    marker->attackKnockback = 2;
    marker->spriteSettings.b16 = player + 7;
    marker->spriteSettings.b20 = marker->spriteSettings.b16;
    marker->spriteSettings.b14 = 2;
    marker->x.HALF.HI = cellX * 16 + 8;
    marker->y.HALF.HI = cellY * 16 + 8;
    marker->animationState = 4;
    marker->health = gameState.health[player];
    RegistObjWork(1, marker);
    playerWork[player].entity = marker;
}
