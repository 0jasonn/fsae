#ifndef WIP_A_SET29_H
#define WIP_A_SET29_H

#include "engine/functions.h"


BOOL test(Entity *e, u16 a, u16 b);

#include "engine/map_state.h"

// Actor fields of the Set29 family, file-local to set29.cpp.
typedef struct Vars_Set29 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 *cellPtr;   // points at this actor's cell in the background map buffer
    /* 7c */ u16 cellValue;  // value of that cell when the actor was placed
} Vars_Set29;

#endif
