#include "engine/functions.h"
#include "actor/enemy/encnt.h"

// plfrontinit (0x02043f70): first run of a spawn slot in front of the player: marks the slot initialised, takes the
// player's facing angle (the animation state when the direction is locked, else the rounded direction) and moves the
// slot by the step table entry for that angle.
void plfrontinit(EncntEntry *e, u16 index) {
    Entity *player;
    int step;

    e->initialised++;
    player = encntState.entity;
    if (player->direction & 0x80) {
        e->angle = player->animationState << 2;
    } else {
        e->angle = (player->direction + 4) & 0x18;
    }
    step = (e->angle + index) * 2;
    e->x += (u16)data_020d4170[step];
    e->y += (u16)data_020d4170[step + 1];
}

// plbackinit (0x02043fec): the same for a slot behind the player (the opposite angle, ^ 0x10).
void plbackinit(EncntEntry *e, u16 index) {
    Entity *player;
    int step;

    e->initialised++;
    player = encntState.entity;
    if (player->direction & 0x80) {
        e->angle = (player->animationState << 2) ^ 0x10;
    } else {
        e->angle = ((player->direction + 4) & 0x18) ^ 0x10;
    }
    step = (e->angle + index) * 2;
    e->x += (u16)data_020d4170[step];
    e->y += (u16)data_020d4170[step + 1];
}
