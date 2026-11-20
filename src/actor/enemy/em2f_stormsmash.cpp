#include "engine/functions.h"
#include "global.h"
#include "actor/enemy/em2f.h"

// em2f_stormSmash (0x020379d8): the storm swing. While the swing counter is below 0x20 it counts up and sets the storm
// timer from the falling part of the sine table; afterwards it waits for the timer, then starts action 0x1d with a sound.
void em2f_stormSmash(Entity *e) {
    u16 index;
    UpdateAnimationSingleFrame(e);
    V(e)->unk_73 += (u8)(s8)V(e)->stormDir;
    index = V(e)->attackCounter;
    if (index < 0x20) {
        V(e)->attackCounter = index + 1;
        V(e)->stormTimer = 0x20 - ((trigTable[V(e)->attackCounter] << 5) >> 8);
        return;
    }
    e->timer -= 1;
    if (e->timer != 0) {
        return;
    }
    V(e)->subPhase = 0xff;
    e->action = 0x1d;
    e->timer = 0x3c;
    EnqueueSFX(0x9f);
}
