#include "engine/functions.h"
#include "global.h"
#include "actor/object/door_silver.h"

extern u8 effectState[];

void door_silver_wait(Entity *e) {
    if (effectState[8] < 3) {
        return;
    }
    if (effectState[2] != e->type2) {
        return;
    }
    e->action++;
    *(u32 *)&e->spriteSettings = (*(u32 *)&e->spriteSettings & ~0xc00) | 0x400;
    displayState.blendCnt = 0x3f40;
    displayState.blendAlpha = 0x10;
    e->timer = 0x10;
    SoundReq(0x7f);
}
