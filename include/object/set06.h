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

#endif
