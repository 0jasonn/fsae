#ifndef OBJECT_DOOR_SILVER_H
#define OBJECT_DOOR_SILVER_H

#include "engine/entity.h"

// Silver door objects, from 0x02069270 (Set31) to 0x0206930c + 0x6c (door_silver_wait).
typedef struct DoorSilverBlock {
    /* 00 */ u8 unk_00[0x66];
    /* 66 */ u16 unk_66;
    /* 68 */ u16 unk_68;
} DoorSilverBlock;

#endif
