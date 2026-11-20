#ifndef ACTOR_OBJECT_REWHALF_H
#define ACTOR_OBJECT_REWHALF_H

#include "engine/functions.h"
#include "engine/player.h"

typedef struct Vars_Rew {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellA;
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 cellB;     // 0xffff when the second cell is unused
    /* 7e */ u16 listSet;   // selects the block of cell lists
} Vars_Rew;
#define VS(e) VARS(Vars_Rew, e)

extern const u16 *const rewHalfListsBgm[];   // rewHalfListsBgm, indexed by the frame's roomNo
extern const u16 *const rewHalfListsPick[];  // rewHalfListsPick, indexed by the pick index

void rewHalf(Entity *e);

#endif
