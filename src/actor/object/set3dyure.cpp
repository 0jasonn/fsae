#include "engine/functions.h"
#include "actor/object/pot.h"

// set3dyure, 0x0205d940. Swings the actor: its vertical speed is pushed 0x800 per frame towards one side until it
// passes +-0x8000, then the sweep reverses; the height follows the speed and the sprite bit 2 is set for the
// directions from 0 to 15.
void set3dyure(Entity *e) {
    int delta;
    switch (e->timer) {
    case 0:
        if (e->zVelocity < -0x8000) {
            e->timer++;
        }
        delta = 0x800;
        break;
    case 1:
        delta = 0x800;
        if (e->zVelocity > 0x8000) {
            e->timer = 0;
        }
        delta = -delta;
        break;
    }
    e->zVelocity -= delta;
    e->z.WORD -= e->zVelocity;
    if (e->direction - 1 < 0xf) {
        SPRITE_WORD(e) |= 4;
    } else {
        SPRITE_WORD(e) &= ~4;
    }
}
