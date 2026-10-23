#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_pika family (module effect_pika), 0x0206ef6c .. 0x0206f034 (dispatcher and init).
// Address -> name: 0x0206ef6c effect_pika, 0x0206ef88 effect_pika_init

// Action table of effect_pika, effectPikaTable
extern const EntityFunc effectPikaTable[];

// Three entries indexed by type2, one table per coordinate
typedef struct PikaOffsetList {
    s32 v[3];
} PikaOffsetList;
extern const PikaOffsetList pikaOffsetX; // pikaOffsetX
extern const PikaOffsetList pikaOffsetY; // pikaOffsetY

ARM void effect_pika(Entity *e) {
    effectPikaTable[e->action](e);
}

ARM void effect_pika_init(Entity *e) {
    u8 action = e->action;
    PikaOffsetList xs;
    PikaOffsetList ys;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    xs = pikaOffsetX;
    ys = pikaOffsetY;
    e->x.HALF.HI = xs.v[e->type2];
    e->y.HALF.HI = ys.v[e->type2] - 0xc;
    e->y.HALF.HI = e->y.HALF.HI + 9;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}
