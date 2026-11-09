#include "engine/functions.h"
#include "actor/object/oplogo_shadow.h"

// 0x020682ac (original name). Initialises the shadow of the opening logo letters.
void oplogo_shadow_init(Entity *e) {
    u8 type = e->type2;

    e->spriteSettings.b0 = 2;
    e->spriteSettings.b14 = type + 1;
    e->spriteSettings.b30 = 1;
    e->speed = (6 - type * 2) << 8;
    e->direction = 0x18;
    e->action++;
    *(u32 *)&e->spriteSettings |= 0x2000;
    InitAnimationForceUpdate(e, (u8)(type + 0xc));
}
