#include "engine/functions.h"
#include "global.h"

// Start positions of the silver doors: three s16 per door type (x, y, value stored in unk_21). Shared with key.cpp.
extern s16 data_02115c78[];

// door_silver_init (0x020692a8): advances the action, sets the sprite priority bits and places the door from the
// per-type position table.
void door_silver_init(Entity *e) {
    e->action++;
    e->spriteSettings.b30 = 2;
    e->spriteSettings.b14 = 2;
    e->spriteSettings.b0 = 2;
    s16 *row = &data_02115c78[e->type * 3];
    e->x.HALF.HI = row[0];
    e->y.HALF.HI = row[1];
    e->unk_21 = row[2];
}
