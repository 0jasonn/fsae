#include "engine/misc_d.h"
#include "global.h"

// Sets the sub-action when the player-state flag at data_0212c5bc+0x12 is set or the player's flag is clear (guess).
ARM void Entity_UpdateSubActionFromPlayers(Entity *e) {
    if (data_0212c5bc[0x12] != 0) {
        e->subAction = 6;
    }
    if (data_0212ceb0[e->type2].unk_03[2] == 0) {
        e->subAction = 6;
    }
}
