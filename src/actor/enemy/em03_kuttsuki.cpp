#include "engine/functions.h"
#include "actor/enemy/em03.h"
#include "global.h"

// em03_kuttsuki (0x0203888c): stuck on the player (child). The attacker's key presses shake it off faster; while it still
// holds, it follows the player with a small wobble and flags the player slot as caught. When the timer runs out or the
// player is hit/knocked (action 2 or 0xf) it lets go with a hop away.
void em03_kuttsuki(Entity *e) {
    Entity *child;

    if (V(e)->unk_6c != 0) {
        V(e)->unk_6c++;
    }
    e->timer--;
    if (playerKeys[e->type] & 0xcf3) {
        if (e->timer < 8) {
            e->timer = 0;
        } else {
            e->timer -= 8;
        }
    }
    child = e->child;
    if (child->action != 2 && child->action != 0xf && e->timer != 0) {
        data_0212ceca[child->type * 0x94] |= 0x80;
        data_0212cee4[child->type * 0x94] = 1;
        ObjPosCopy(child, e);
        e->x.HALF.HI += data_020d1844[(frameCounter.frame & 0x1c) >> 1];
        e->y.HALF.HI += data_020d1844[((frameCounter.frame & 0x1c) >> 1) + 1];
        e->unk_5e.b0 = 3;
    } else if (data_0212ceb2[e->type2 * 0x94] == 0) {
        e->action++;
        e->unk_2e = 2;
        e->direction = ((e->child->animationState & 6) ^ 4) << 2;
        e->speed += 0x40;
        e->zVelocity = 0x1c000;
        e->iframes = 0xdc;
        e->unk_5c = 0x21ff;
        data_0212ceca[e->child->type * 0x94] = 0;
    }
}
