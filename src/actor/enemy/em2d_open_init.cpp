#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"
#include "actor/enemy/em2d.h"

// openInit (0x02035a8c): picks a random sprite colour group (7 + Random() % players) for the flower, passes a new random
// one (wireless mode with phaseFlags set) or its own group to the petal, and starts the open animations.
// The petal's b16 = b20 copy is written in both branches: the compiler merges the two copies into one tail, which keeps
// the following `mov r1, #5` out of that block (with one copy after the if/else it is hoisted and the petal pointer
// moves to r3).
void openInit(Entity *e) {
    void *app;

    e->spriteSettings.b20 = (Random() % gameState.playerCount) + 7;
    e->spriteSettings.b16 = e->spriteSettings.b20;
    if (V(e)->petal != NULL) {
        app = KnifeApp_getInstance();
        if (V(e)->phaseFlags != 0 && KnifeApp_isWirelessMode(app) != 0) {
            V(e)->petal->spriteSettings.b20 = (Random() % gameState.playerCount) + 7;
            V(e)->petal->spriteSettings.b16 = V(e)->petal->spriteSettings.b20;
        } else {
            V(e)->petal->spriteSettings.b20 = e->spriteSettings.b16;
            V(e)->petal->spriteSettings.b16 = V(e)->petal->spriteSettings.b20;
        }
        V(e)->petal->spriteSettings.b0 = 1;
        InitAnimationForceUpdate(V(e)->petal, 5);
    }
    InitAnimationForceUpdate(e, 4);
    EnqueueSFX(0xa2);
}
