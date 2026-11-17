#include "engine/functions.h"
#include "engine/player.h"
#include "engine/misc.h"

// kenfuri_wait2, 0x02072fc8. When game flag 0x20 is set the actor leaves its wait: it picks its facing from its
// type, starts moving at speed 0x100, advances the sub action and puts its player into motion 4.
void kenfuri_wait2(Entity *e) {
    int facing;
    if ((data_02134924 & 0x20) == 0) {
        return;
    }
    facing = 6;
    if (e->type > 1) {
        facing = 2;
    }
    e->animationState = facing;
    e->direction = e->animationState << 2;
    e->speed = 0x100;
    e->timer = 0xc;
    e->subAction++;
    playerWork[e->type].motionId = 4;
}
