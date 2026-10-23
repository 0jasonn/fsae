#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_beam3 family (module effect_beam3), (dispatcher and init).
// Address -> name: 0x0206ee40 effect_beam3, 0x0206ee5c effect_beam3_init

// Action table of effect_beam3, effectBeam3Table
extern const EntityFunc effectBeam3Table[];

// Three entries indexed by type2, one table per coordinate
typedef struct Beam3OffsetList {
    s32 v[3];
} Beam3OffsetList;
extern const Beam3OffsetList beam3OffsetX; // beam3OffsetX
extern const Beam3OffsetList beam3OffsetY; // beam3OffsetY

ARM void effect_beam3(Entity *e) {
    effectBeam3Table[e->action](e);
}

ARM void effect_beam3_init(Entity *e) {
    u8 action = e->action;
    Beam3OffsetList xs;
    Beam3OffsetList ys;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    xs = beam3OffsetX;
    ys = beam3OffsetY;
    e->x.HALF.HI = xs.v[e->type2];
    e->y.HALF.HI = ys.v[e->type2] - 0x4;
    e->y.HALF.HI = e->y.HALF.HI + 9;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}
