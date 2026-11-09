#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "ui/message.h"
#include "actor/object/frontcheck_a.h"

// Uses a key of the entity's player (GameState::unk_5c[type]) or, for player 0 in single play, the shared key counter
// unk_5c[1]. Returns 1 when a key was used.
BOOL TryUsingKey(Entity *e) {
    if (gameState.unk_5c[e->type] != 0) {
        gameState.unk_5c[e->type] -= 1;
        cockpitState[2] = 1;
        return 1;
    }
    if (KnifeApp_isWirelessMode(KnifeApp_getInstance()) == 0 && e->type == 0) {
        if (Knife_Single_SinglePlay_GetInstance()[1] != 0 && gameState.unk_5c[1] != 0) {
            gameState.unk_5c[1] -= 1;
            cockpitState[2] = 1;
            return 1;
        }
    }
    return 0;
}
