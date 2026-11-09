#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/before_player.h"

// 0x02054894 BeforePlayer (original name, C linkage): drops the player's y offset into the entity and clears the
// flag 0x200 of its status word.

void BeforePlayer(Entity *e) {
    playerWork[e->type].statusFlags &= ~0x200;
    e->y.HALF.HI -= playerWork[e->type].yOffset;
    playerWork[e->type].yOffset = 0;
    if (playerWork[e->type].statusFlags & 0x400) {
        func_0208919c(e);
    }
}
