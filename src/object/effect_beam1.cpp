#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_beam1 family (module effect_beam1), 0x0206eba0 .. 0x0206ec68 (dispatcher and init).
// Address -> name: 0x0206eba0 effect_beam1, 0x0206ebbc effect_beam1_init

// Action table of effect_beam1, effectBeam1Table
extern const EntityFunc effectBeam1Table[];

// Three entries indexed by type2, one table per coordinate
typedef struct BeamOffsetList {
    s32 v[3];
} BeamOffsetList;
extern const BeamOffsetList beam1OffsetX; // beam1OffsetX
extern const BeamOffsetList beam1OffsetY; // beam1OffsetY

ARM void effect_beam1(Entity *e) {
    effectBeam1Table[e->action](e);
}

ARM void effect_beam1_init(Entity *e) {
    u8 action = e->action;
    BeamOffsetList xs;
    BeamOffsetList ys;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    xs = beam1OffsetX;
    ys = beam1OffsetY;
    e->x.HALF.HI = xs.v[e->type2];
    e->y.HALF.HI = ys.v[e->type2] - 0xc;
    e->y.HALF.HI = e->y.HALF.HI + 9;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}
