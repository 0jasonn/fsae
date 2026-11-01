#ifndef OBJECT_SET2C_H
#define OBJECT_SET2C_H

#include "engine/entity.h"

typedef struct Vars_Set2c {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(e->type2), tested against em12_typeMasks[e->areaIndex]
    /* 64 */ u32 flagMask; // flagBits[e->type], set or cleared in em12_typeMasks
} Vars_Set2c;

#endif
