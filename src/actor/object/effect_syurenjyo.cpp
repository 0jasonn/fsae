#include "engine/functions.h"
#include "global.h"
#include "actor/object/ss.h"
#include "actor/object/effectdecls.h"

// effect_syurenjyo family (module effect_syurenjyo), 0x0206e3d0 .. 0x0206e3ec (dispatcher only).
// Address -> name: 0x0206e3d0 effect_syurenjyo, 0x0206e3ec effect_syurenjyo_init, 0x0206e454 effect_syurenjyo_move

// Action table of effect_syurenjyo, effectSyurenjyoTable
extern const EntityFunc effectSyurenjyoTable[];

void effect_syurenjyo(Entity *e) {
    effectSyurenjyoTable[e->action](e);
}
