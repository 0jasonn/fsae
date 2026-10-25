#ifndef WIP_A_PAIR_BLOCK_H
#define WIP_A_PAIR_BLOCK_H

#include "global.h"
#include "types.h"

// Block at data_02129cac: the write cursor at +0, flags at +4 (bit 0 selects the pair) and the buffer at +8.
typedef struct PairBlock {
    u8 *cursor;
    u32 flags;
    void *pair;
} PairBlock;

extern PairBlock data_02129cac;

#endif
