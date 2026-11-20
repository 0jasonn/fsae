#include "engine/functions.h"
#include "global.h"
#include "engine/bg_buff.h"
#include "actor/object/pot.h"

// Grass throw actor, dispatcher (module grass). Address -> name:
//   0x0205ed90 grass_throw (original name, state table grass_throw_states indexed by e->subAction)
//   (grass_throw_init at 0x0205edac is in the next unit)

extern const EntityFunc grass_throw_states[]; // state table indexed by e->subAction

void grass_throw(Entity *e) {
    grass_throw_states[e->subAction](e);
}

// Grass throw actor, init (module grass). Address -> name:
//   0x0205edac grass_throw_init (original name throw_init)
//   (grass_throw at 0x0205ed90 is in grass_1.cpp, the next unit starts at Throw_NoOp 0x0205ee78)

void grass_throw_init(Entity *e) {
    Vars_Pot *v = VARS(Vars_Pot, e);
    BG_BUFF_ *bg;
    int cell;

    bg = (BG_BUFF_ *)GetBgBuffAdrs(e->layer);
    e->hitbox = grass_hitbox;
    e->statusFlags = 0x89;
    e->poseId = 1;
    e->unk_5c = playerWork[e->type2].entity->unk_5c & 0x55;
    cell = MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI);
    bg->screen[cell] = v->savedCell;
    cell = MAP_CELL_INDEX(e->x.HALF.HI, e->y.HALF.HI);
    bg->attr[cell] = v->savedCellState;
    e->subAction = e->subAction + 1;
}
