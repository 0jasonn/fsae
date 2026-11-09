#include "engine/functions.h"
#include "global.h"
#include "actor/object/set13.h"
#include "actor/object/set13_cell.h"

// Set13 cell helpers (module set13). Address -> name:
//   0x020647d0 hidari_rewritecell (original rewritecell): writes the two saved cell values around the actor's cell
//   0x02064814 cellcheck (original name): nonzero unless all three cells still hold the expected value

void hidari_rewritecell(Entity *e) {
    s8 step = *(const s16 *)((const u8 *)cellDeltaTable + (e->animationState & ~1));
    u16 *cell = VARS(Vars_Set13, e)->cellPtr + step;
    *cell = VARS(Vars_Set13, e)->cellValue70;
    cell -= step;
    *(cell - step) = VARS(Vars_Set13, e)->cellValue74;
}

int cellcheck(Entity *e) {
    s8 step = *(const s16 *)((const u8 *)cellDeltaTable + (e->animationState & ~1));
    u16 expected = *(const u16 *)((const u8 *)set13_cellValueTable + (e->animationState & ~1));
    u16 *cell = VARS(Vars_Set13, e)->cellPtr + step;

    if (expected != *cell) {
        return 1;
    }
    cell -= step;
    if (expected != *cell) {
        return 1;
    }
    cell -= step;
    return expected != *cell;
}
