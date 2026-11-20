#include "engine/functions.h"
#include "actor/enemy/em29.h"
#include "global.h"

// em31_init, 0x020432dc. Sets up a fresh entity; type 0 keeps sprite bit 0 only. A direction of 0xff is replaced by a
// random heading towards a point near the scroll origin, a zero speed takes a random one from a table, then the
// script starts and the sprite bit 2 follows the direction.
void em31_init(Entity *e) {
    e->action = 1;
    e->spriteSettings.b0 = 1;
    e->unk_2e = 4;
    e->z.HALF.HI = -2;
    e->hitbox = data_020d35f4;
    if (e->type != 0) {
        e->spriteSettings.b4 = 1;
    }
    if (e->direction == 0xff) {
        u32 first = Random();
        u32 second = Random();
        e->direction = CalculateDirectionTo(e->x.HALF.HI, e->y.HALF.HI, (first & 0x1f) + 0x1d8, (second & 0x1f) + 0x1e8);
    }
    if (e->speed == 0) {
        e->speed = data_020d35ec[Random() & 3];
    }
    Enemy_StartScript(e);
    if (e->direction & 0xf) {
        SPRITE_BIT2(e)->bit2 = (e->direction >> 4) ^ 1;
    }
    InitAnimationForceUpdate(e, 0);
}
