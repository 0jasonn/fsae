#ifndef WIP_B_WANWAN_H
#define WIP_B_WANWAN_H

#include "engine/entity.h"

// Calls that are not in engine/functions.h yet (reviewer: move to functions.h).

// Wanwan (bow-wow chain actor) functions, 0x0208139c and 0x02081a8c.
void wanwan_init(Entity *e);
s32 wanwan_rangeCk(Entity *a, Entity *b, s16 radius);

#endif
