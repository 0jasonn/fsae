#ifndef WIP_A_SET29_H
#define WIP_A_SET29_H

#include "engine/functions.h"

// Not in engine/functions.h yet (original RewCellOne(unsigned short, unsigned short, unsigned short), 0x02021a94).
void RewCellOne(u16 a, u16 b, u16 c);

BOOL test(Entity *e, u16 a, u16 b);

// Grid origin at data_0212c648 (shared; the origin fields are at +0x18 and +0x1a).
typedef struct OplogoGridOrigin {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 originX;
    /* 1a */ u16 originY;
} OplogoGridOrigin;
extern OplogoGridOrigin data_0212c648;

// Actor fields of the Set29 family, file-local to set29.cpp.
typedef struct Vars_Set29 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 *cellPtr;   // points at this actor's cell in the background map buffer
    /* 7c */ u16 cellValue;  // value of that cell when the actor was placed
} Vars_Set29;

#endif
