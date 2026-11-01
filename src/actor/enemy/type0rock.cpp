#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

// Functions in this file: type0rockonSet (0x0203e038).

void type0rockonSet(Entity *e) {
    e->action = 1;
    e->timer = data_0212c7c8.playerCount;
    e->child = 0;
}
