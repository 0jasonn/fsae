#include "engine/functions.h"
#include "global.h"
#include "object/cellcalls.h"
#include "object/set34_2.h"

// Set34 family, move unit (module set34). Address -> name:
//   0x0206ae0c set34_move (original name)

typedef struct Vars_Set34 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellIndex; // map cell of the actor (word 0x78)
    /* 7a */ u8 unk_7a;
    /* 7b */ u8 cellMode;   // mode passed to func_0208365c
} Vars_Set34;

// set34_move, 0x0206ae0c: unless heart_areaCheck reports the actor, marks the cells around it with cellMode
extern "C" void set34_move(Entity *e);

ARM void set34_move(Entity *e) {
    if (heart_areaCheck(e) != 0) {
        return;
    }
    switch (e->type) {
    case 3:
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 3), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x43), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x83), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0xc0), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0xc1), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0xc2), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0xc3), e->layer);
        /* fall through */
    case 2:
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 2), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x42), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x80), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x81), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x82), e->layer);
        /* fall through */
    case 1:
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 1), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x40), e->layer);
        func_0208365c(VARS(Vars_Set34, e)->cellMode, (u16)(VARS(Vars_Set34, e)->cellIndex + 0x41), e->layer);
        /* fall through */
    case 0:
        func_0208365c(VARS(Vars_Set34, e)->cellMode, VARS(Vars_Set34, e)->cellIndex, e->layer);
        break;
    }
    PutObjWork(e);
}
