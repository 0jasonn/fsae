#include "engine/functions.h"
#include "global.h"
#include "game/encnt.h"

// housha1: moves a free spawn slot along a random direction. On the first call the direction is picked at random (0..63);
// every call adds the step of that direction (trigTable, sine and cosine in 1/16 steps) to the slot position, wrapped to the
// 0x3ff range.
void housha1(EncntEntry *e, u16 index) {
    if (e->initialised == 0) {
        e->initialised++;
        e->angle = Random() & 0x3f;
    }
    e->x = (e->x + ((trigTable[e->angle * 4] << 4) >> 8)) & 0x3ff;
    e->y = (e->y + ((trigTable[e->angle * 4 + 0x40] << 4) >> 8)) & 0x3ff;
}
