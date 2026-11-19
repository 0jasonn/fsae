#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

// magneInit (0x02049cdc): attaches a magnet shadow to the player's weapon slot and copies the owner's sprite flags.
void magneInit(Entity *e) {
    Entity *player = playerWork[e->type].entity;
    playerWork[e->type].weapon = e;
    e->spriteSettings.b0 = 1;
    e->action++;
    e->spriteSettings.b16 = 4;
    e->unk_1b = 0x14;
    e->timer = 8;
    e->animationState = player->animationState & 0xe;
    e->spriteSettings.b14 = player->spriteSettings.b14;
    e->spriteSettings.b30 = player->spriteSettings.b30;
    e->unk_20 = player->unk_20;
    e->spriteSettings.b6 = player->spriteSettings.b6;
    func_0208ab14(e, player);
    magneMove(e);
}
