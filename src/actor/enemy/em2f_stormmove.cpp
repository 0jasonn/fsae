#include "engine/functions.h"
#include "actor/enemy/em2f.h"
#include "global.h"

// stormMove (0x02038414): one step of the storm swing, adds the swing direction to the angle byte and sets the storm timer
// from the rising part of the sine table; the counter wraps at 0x80.
void stormMove(Entity *e) {
    s32 index;
    V(e)->unk_73 += (u8)(s8)V(e)->stormDir;
    index = V(e)->attackCounter;
    V(e)->stormTimer = ((trigTable[index] << 5) >> 8) + 0x20;
    V(e)->attackCounter = (index + 1) & 0x7f;
}