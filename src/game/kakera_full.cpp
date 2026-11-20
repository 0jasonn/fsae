#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "engine/cockpit_state.h"
#include "game/kakera_full.h"

// Turns four kakera of the entity's player (GameState::kakeraCount) into rupees: 250 with the unk_24 flag, otherwise 500.
void AddKakeraFull(Entity *e) {
    s32 amount;

    if (gameState.kakeraCount[e->type] >= 4) {
        gameState.kakeraCount[e->type] -= 4;
        amount = gameState.unk_24 != 0 ? 250 : 500;
        AddRupee(e, (s16)amount);
        SoundReq(0xf);
        if (gameState.kakeraCount[e->type] >= 4) {
            cockpitState.kakeraTimer[e->type] = 0x1e;
        }
    }
}
