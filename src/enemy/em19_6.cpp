#include "engine/functions.h"
#include "global.h"
#include "enemy/em19_6.h"
#include "enemy/em19_api.h"

// Functions in this file: Em19 (0x0203e05c), the em19 actor entry. Type 2 runs the state table em19_stateTable
// (em19_stateTable) through EnemyFunctionHandler and copies the position from the parent with bgobj_poscopy;
// other types dispatch on e->action.

extern const u8 em19_stateTable[];

// Em19 (0x0203e05c), plain name in the ROM

void Em19(Entity *e) {
    if (e->type == 2) {
        EnemyFunctionHandler(e, em19_stateTable);
        if (e->parent != 0) {
            bgobj_poscopy(e);
        }
        return;
    }
    em19_mainTable[e->action](e);
}
