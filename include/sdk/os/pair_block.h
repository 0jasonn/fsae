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

// Start of the 0x300-byte pair buffer: a 64-bit value (the pair itself), a kind byte, a 16-bit value copied from the
// shared area at 0x02ffe010 and the CRC16 of the whole buffer (computed with the CRC field cleared).
typedef struct PairBufferHeader {
    u64 pair;       // 0x00
    u8 unk_08;      // 0x08
    u8 kind;        // 0x09: bit 0 is cleared by Pair_Restore, Pair_Commit stores 3
    u16 shared;     // 0x0a
    u16 unk_0c[2];  // 0x0c
    u16 crc;        // 0x10
} PairBufferHeader;

extern PairBlock data_02129cac;
extern u64 data_02129cb8; // copy of the first 8 bytes of the pair buffer taken by Pair_Commit

// The deliver-argument module (0x02019c0c .. 0x02019d08): Pair_Restore, OS_DisableMainExArena (clears flags; the dsd name
// does not fit what it does), Pair_GetIfEnabled, OS_IsValidDeliverArg.
extern "C" {
s32 Pair_Commit(void); // not decompiled yet (parked)
void OS_DisableMainExArena(void);
BOOL OS_IsValidDeliverArg(void);
}

#endif
