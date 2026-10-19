#include "engine/functions.h"
#include "global.h"
#include "object/setcommon.h"

// Rader child actor, second unit (module rader). Address -> name:
//   0x02063400 rc_init (original name)

ARM void rc_init(Entity *e) {
    e->unk_1b = 0x15;
    e->spriteSettings.b16 = e->type2 + 7;
    e->action++;
    e->timer = 8;
    e->x.HALF.HI = 6;
    e->y.HALF.HI = 6;
    InitAnimationForceUpdate(e, e->type2);
}
