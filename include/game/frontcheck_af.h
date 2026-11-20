#ifndef WIP_FRONTCHECK_AF_H
#define WIP_FRONTCHECK_AF_H

#include "engine/functions.h"
#include "engine/player.h"


extern u32 data_02134bb0[]; // 8 byte records: [0] cell / layer / direction word, [1] entity pointer
extern u8 data_021348e4;    // number of records in data_02134bb0 (at most 0x10)
extern s16 data_020cd704[]; // x / y offset pairs in front of the actor, indexed by animationState & 6

extern "C" {
BOOL FrontCheckAF(Entity *e, PlayerData *player); // 0x020233f0, plain name in the original
}

#endif
