#ifndef OBJECT_SET06_H
#define OBJECT_SET06_H

#include "engine/entity.h"

typedef struct UnkStruct_0212c648_S {
    /* 00 */ u8 unk_00[0x18];
    /* 18 */ u16 scrollX;
    /* 1a */ u16 scrollY;
} UnkStruct_0212c648_S;

typedef struct WWORK {
    s16 x; // offset added to the entity's x (integer half)
    s16 y; // offset added to the entity's y (integer half)
} WWORK;

typedef struct Vars_Set06 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 bits; // one bit per type group covered by this set (set06_init)
    /* 64 */ WWORK posStep; // offset applied when the set moves forward
    /* 68 */ WWORK posBack; // offset applied when the set moves back
    /* 6c */ u16 cellId; // id passed to RewCell
} Vars_Set06;

#endif
