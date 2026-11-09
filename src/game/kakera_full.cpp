#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"
#include "game/kakera_full.h"

extern u16 data_0212c63c[]; // per-player counter set to 0x1e while another full set of kakera is waiting

// Turns four kakera of the entity's player (GameState::playerFlag68) into rupees: 250 with the unk_24 flag, otherwise 500.
void AddKakeraFull(Entity *e) {
    s32 amount;

    if (gameState.playerFlag68[e->type] >= 4) {
        gameState.playerFlag68[e->type] -= 4;
        amount = gameState.unk_24 != 0 ? 250 : 500;
        AddRupee(e, (s16)amount);
        SoundReq(0xf);
        if (gameState.playerFlag68[e->type] >= 4) {
            data_0212c63c[e->type] = 0x1e;
        }
    }
}
