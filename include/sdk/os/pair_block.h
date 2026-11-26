#ifndef SDK_OS_PAIR_BLOCK_H
#define SDK_OS_PAIR_BLOCK_H

#include "global.h"
#include "types.h"

// Block at data_02129cac: the write cursor at +0, flags at +4 (bit 0 selects the pair) and the buffer at +8.
typedef struct PairBlock {
    u8 *cursor;
    u32 flags;
    void *pair;
} PairBlock;

extern PairBlock data_02129cac;

// The deliver-argument module (0x02019c0c .. 0x02019d08): Pair_Restore, OS_DisableMainExArena (clears flags; the dsd name
// does not fit what it does), Pair_GetIfEnabled, OS_IsValidDeliverArg.
extern "C" {
void OS_DisableMainExArena(void);
BOOL OS_IsValidDeliverArg(void);
}

#endif
