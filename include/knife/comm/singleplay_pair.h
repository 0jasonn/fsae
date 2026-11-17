#ifndef KNIFE_COMM_SINGLEPLAY_PAIR_H
#define KNIFE_COMM_SINGLEPLAY_PAIR_H

#include "types.h"
#include "engine/entity.h"
#include "engine/player.h"
#include "knife/comm/single_cmd_api.h"

// abs_s32 is a C++ function (symbols.txt: _Z7abs_s32l)
s32 abs_s32(s32 value);

extern u8 data_0212caf0[]; // data block of player 0 (the pair work item points at it)
extern u8 data_0212cb60[]; // data block of player 1

#endif
