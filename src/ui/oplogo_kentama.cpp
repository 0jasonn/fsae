#include "engine/functions.h"
#include "global.h"
#include "actor/object/object_handlers.h"

// oplogo_kentama (0x0206884c): the sword-ball sprite of the opening logo; appears at (0x80, 0x60) and removes itself after 8 frames.
void oplogo_kentama(Entity *e) {
    switch (e->action) {
    case 0:
        *(u32 *)&e->spriteSettings |= 0x2000; // sets bit 5 of the b8 field
        e->spriteSettings.b0 = 2;
        e->action++;
        e->spriteSettings.b14 = 0;
        e->spriteSettings.b30 = 1;
        e->x.HALF.HI = 0x80;
        e->y.HALF.HI = 0x60;
        e->timer = 8;
        InitAnimationForceUpdate(e, (u8)(8 + e->type2));
        break;
    case 1:
        if (--e->timer != 0) {
            break;
        }
        PutObjWork(e);
        break;
    }
}
