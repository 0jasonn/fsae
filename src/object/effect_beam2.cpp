#include "engine/functions.h"
#include "global.h"
#include "object/ss.h"
#include "object/effectdecls.h"

// effect_beam2 family (module effect_beam2), 0x0206ecdc .. 0x0206edbc (dispatcher and init).
// Address -> name: 0x0206ecdc effect_beam2, 0x0206ecf8 effect_beam2_init

// Action table of effect_beam2, effectBeam2Table
extern const EntityFunc effectBeam2Table[];

// Six entries indexed by type2, one table per coordinate
typedef struct Beam2OffsetList {
    s32 v[6];
} Beam2OffsetList;
extern const Beam2OffsetList beam2OffsetX; // beam2OffsetX
extern const Beam2OffsetList beam2OffsetY; // beam2OffsetY

ARM void effect_beam2(Entity *e) {
    effectBeam2Table[e->action](e);
}

ARM void effect_beam2_init(Entity *e) {
    u8 action = e->action;
    Beam2OffsetList xs;
    Beam2OffsetList ys;

    e->action = action + 1;
    e->spriteSettings.b14 = 3;
    e->spriteSettings.b30 = 1;
    e->timer = 0;
    e->subtimer = 0;
    xs = beam2OffsetX;
    ys = beam2OffsetY;
    e->x.HALF.HI = xs.v[e->type2];
    e->y.HALF.HI = ys.v[e->type2] - 0x8;
    e->y.HALF.HI = e->y.HALF.HI + 9;
    InitAnimationForceUpdate(e, e->type);
    effectPhaseTable[e->type2] = 0;
}
