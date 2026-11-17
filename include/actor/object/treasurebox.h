#ifndef WIP_TREASUREBOX_H
#define WIP_TREASUREBOX_H

#include "engine/functions.h"

extern "C" void takaraAddEntry(Entity *e, u8 handlerIndex); // 0x020772f0, defined in actor/object/takara_entry.cpp

// Order of the 12 chest slots before shuffling (data_020dc65c) and the (x, y) cell pairs of the slots (data_020dc623).
typedef struct TreasureOrder {
    u8 slot[12];
} TreasureOrder;
extern const TreasureOrder data_020dc65c;
extern const u8 data_020dc623[];
extern u32 em12_typeMasks[];

#endif
