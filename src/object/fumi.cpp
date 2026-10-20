#include "engine/functions.h"
#include "global.h"
#include "object/objdecls_f.h"

// Fumi (step switch) check, module fumi. Address -> name:
//   0x0205b5bc fumiCheck (original name)
//   0x0205b630 fumiCheck2 (original name)

typedef struct Vars_Fumi {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellEvent; // result of func_0208367c, 0xffff when none
    /* 7a */ u16 cellKind;  // result of func_02083ca8 for the last cell
    /* 7c */ u16 cell;      // cell of the actor with the grid origin
    /* 7e */ u8 event;      // argument of func_0208365c
} Vars_Fumi;

ARM int fumiCheck(Entity *e) {
    int result;
    int kind;

    result = func_02084110();
    if (result != 0) {
        VARS(Vars_Fumi, e)->cellEvent = 0xffff;
        return result;
    }
    kind = func_02083ca8(VARS(Vars_Fumi, e)->cell, e->layer);
    if (kind == 0x148 || kind == 0x14a || kind == VARS(Vars_Fumi, e)->cellKind) {
        return 0;
    }
    VARS(Vars_Fumi, e)->cellEvent = func_0208367c(VARS(Vars_Fumi, e)->cell, e->layer);
    VARS(Vars_Fumi, e)->event = func_02083d4c(VARS(Vars_Fumi, e)->cell, e->layer);
    return 0x10;
}

ARM int fumiCheck2(Entity *e) {
    int result;

    result = func_02084110();
    if (result != 0) {
        return result;
    }
    if (VARS(Vars_Fumi, e)->cellEvent != 0xffff) {
        if (VARS(Vars_Fumi, e)->cellEvent == func_0208367c(VARS(Vars_Fumi, e)->cell, e->layer)) {
            return 0x10;
        }
    }
    return 0;
}
