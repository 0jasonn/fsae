#include "engine/functions.h"
#include "global.h"
#include "object/set24.h"

// Set24 actor (module set24). Address -> name:
//   0x020664c8 Set24 (dispatcher, was Set24)
//   0x020664e4 set24_init, 0x0206652c set24_move

// Dispatcher: runs the handler for the current action.
ARM void Set24(Entity *e) {
    set24_stateTable[e->action](e);
}

// Init: starts a short upward flight in a random direction.
ARM void set24_init(Entity *e) {
    e->action++;
    e->hitbox = set24_hitbox;
    e->zVelocity = 0x1c000;
    e->direction = Random() & 0x1f;
    e->speed = 0x100;
    e->timer = 10;
}

// Moves for the timer, then falls. Copies the position to the linked entity, which is removed once it lands.
ARM void set24_move(Entity *e) {
    if (e->timer != 0) {
        MoveDir(e);
        e->timer--;
    } else {
        func_020852ec(e);
    }
    if (UpdateGravity(e, 0x2400) != 0) {
        e->contactedEntity->spriteSettings.b14 = 0;
    } else {
        e->contactedEntity->spriteSettings.b14 = 3;
        PutObjWork(e);
    }
    e->contactedEntity->x.WORD = e->x.WORD;
    e->contactedEntity->y.WORD = e->y.WORD;
    e->contactedEntity->z.WORD = e->z.WORD;
}
