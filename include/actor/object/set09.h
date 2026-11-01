#ifndef OBJECT_SET09_H
#define OBJECT_SET09_H

#include "engine/entity.h"

typedef struct Vars_Set09 {
    /* 00 */ u8 unk_00[0x62];
    /* 62 */ u16 spawnCount; // number of spawned objects, incremented by set6b_setenemy
    /* 64 */ u16 unk_64;     // bit word, OR-ed with flagBits[slot]; passed to CountBits / func_02084634
    /* 66 */ u8 unk_66[2];
    /* 68 */ u32 typeBits;   // bits from ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 6c */ u8 unk_6c[4];
    /* 70 */ const u16 *info; // table from GetInfoAdrs, 8-byte entries ended by 0xffff
} Vars_Set09;

#endif
