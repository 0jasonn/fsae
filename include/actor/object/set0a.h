#ifndef OBJECT_SET0A_H
#define OBJECT_SET0A_H

#include "engine/entity.h"

// File-local fields of the set actors (Entity bytes from 0x6c on).
typedef struct SetVars {
    /* 00 */ u8 unk_00[0x6c];
    /* 6c */ u16 retainFlag; // nonzero: the action table is skipped while encntSharedState is 0
    /* 6e */ u8 unk_6e[2];
    /* 70 */ u8 setKind;
    /* 71 */ u8 setParam1;
    /* 72 */ u8 setParam2;
} SetVars;

#endif
