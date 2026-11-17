#include "engine/functions.h"
#include "engine/player.h"

// warphole_init, 0x0205de50. Starts the warp hole hidden from the sprite layers; while the game state is active it
// shows itself and skips the first wait action.
void warphole_init(Entity *e) {
    e->action++;
    e->statusFlags = 0;
    e->timer = 0x1e;
    e->subtimer = 0;
    e->spriteSettings.b14 = 3;
    e->unk_5e.b0 = 0;
    if (gameState.active != 0) {
        e->spriteSettings.b0 = 1;
        e->action++;
    }
    InitAnimationForceUpdate(e, 0);
}
