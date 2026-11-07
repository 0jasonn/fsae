#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em20.h"
#include "actor/enemy/em20_6.h"

// em20 actor, eighth unit: em20_atafutaInit (0x0203ebd4), em20_atafuta (0x0203ec50).

// Waits for the fall to end (gravity 0x1c00), flipping the facing every 32 frames, then switches to action 8.
void em20_atafutaInit(Entity *e) {
    if (e->timer != 0) {
        if ((e->timer & 0x1f) == 0) {
            e->animationState ^= 2;
            e->direction = e->animationState << 3;
            InitAnimationForceUpdate(e, e->animationState + 4);
        }
        e->timer--;
    } else {
        if (UpdateGravity(e, 0x1c00) != 0) {
            return;
        }
        e->action = 8;
        e->timer = 0x1e;
        e->speed = 0x120;
    }
}

// Every 0x1e frames picks a new random facing direction and restarts the animation when the facing changed.
void em20_atafuta(Entity *e) {
    func_020847a0(e);
    UpdateAnimationSingleFrame(e);
    if (--e->timer != 0) {
        return;
    }
    e->timer = 0x1e;
    e->direction = Random() & 0x18;
    if (e->direction >> 3 == e->animationState) {
        return;
    }
    e->animationState = e->direction >> 3;
    InitAnimationForceUpdate(e, e->animationState + 4);
}
