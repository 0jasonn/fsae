#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

// Functions in this file: type0rockonSet (0x0203e038).

void type0rockonSet(Entity *e) {
    e->action = 1;
    e->timer = gameState.playerCount;
    e->child = 0;
}
