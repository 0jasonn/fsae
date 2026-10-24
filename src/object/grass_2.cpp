#include "engine/functions.h"
#include "global.h"
#include "object/c_decls.h"

// Grass throw actor, init (module grass). Address -> name:
//   0x0205edac grass_throw_init (original name throw_init)
//   (grass_throw at 0x0205ed90 is in grass_1.cpp, the next unit starts at Throw_NoOp 0x0205ee78)

ARM void grass_throw_init(Entity *e) {
    Vars_Pot *v = VARS(Vars_Pot, e);
    u8 *bg;
    int cell;

    bg = (u8 *)GetBgBuffAdrs(e->layer);
    e->hitbox = grass_hitbox;
    e->statusFlags = 0x89;
    e->poseId = 1;
    e->unk_5c = data_0212ceb0[e->type2].entity->unk_5c & 0x55;
    cell = MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI);
    *(u16 *)(bg + cell * 2 + 4) = v->savedCell;
    cell = MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI);
    *(bg + cell + 0x2004) = v->savedCellState;
    e->subAction = e->subAction + 1;
}
