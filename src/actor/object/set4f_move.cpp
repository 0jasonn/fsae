#include "engine/functions.h"
#include "global.h"
#include "actor/object/set4f_actions.h"

// Set4f actor (module set4f), action 2. Address -> name:
//   0x0205e914 set4f_move (original name)

typedef struct Vars_Set4fMove {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u8 lastState;      // value of *statePtr last time it changed
    /* 79 */ u8 rewritePending; // set while the cell is being rewritten
    /* 7a */ u16 cell;          // cell position from the actor's x/y
    /* 7c */ u8 *statePtr;      // byte in the background buffer that drives this actor
} Vars_Set4fMove;

// Removes the actor once its cell has become kind 1; otherwise rewrites the cell whenever the watched state byte
// changes and waits for it to settle again.
void set4f_move(Entity *e) {
    Vars_Set4fMove *v = VARS(Vars_Set4fMove, e);

    if (GetCellKind(v->cell, e->layer) == 1) {
        if ((e->layer >> 14) != 2) {
            func_02083694(0x2f, v->cell, e->layer);
        } else {
            func_02083694(0x58, v->cell, e->layer);
        }
        PutObjWork(e);
        return;
    }
    if (v->rewritePending) {
        if (*v->statePtr != 0) {
            v->rewritePending = 0;
        }
        return;
    }
    if (v->lastState == *v->statePtr) {
        return;
    }
    v->rewritePending = 1;
    RewCell(set4f_rewriteIds[e->type], v->cell, e->layer);
}
