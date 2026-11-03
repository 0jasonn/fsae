#include "engine/functions.h"
#include "global.h"
#include "actor/object/setcommon.h"

// Radar (rader) child object. Address -> name:
//   0x020633bc raderChild (original name)

extern const EntityFunc raderChildTable[]; // raderChildTable, indexed by e->action

void raderChild(Entity *e) {
    raderChildTable[e->action](e);
    e->spriteSettings.b14 = 0;
    e->unk_5e.b0 = 3;
    e->spriteSettings.b30 = 1;
}

// Rader child actor, second unit (module rader). Address -> name:
//   0x02063400 rc_init (original name)

void rc_init(Entity *e) {
    e->unk_1b = 0x15;
    e->spriteSettings.b16 = e->type2 + 7;
    e->action++;
    e->timer = 8;
    e->x.HALF.HI = 6;
    e->y.HALF.HI = 6;
    InitAnimationForceUpdate(e, e->type2);
}
