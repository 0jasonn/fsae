#ifndef WIP_D_WIRELESS_MANAGER_D_H
#define WIP_D_WIRELESS_MANAGER_D_H

#include "types.h"

// Knife::Comm::WirelessManager fields used by the D units. Offsets from the start of the manager. Only the fields
// the functions so far read or write are named; the rest is kept as bytes.
typedef struct WirelessManagerWork {
    u8 unk_0000[0x1c9c];
    void *allocator;         // 0x1c9c: the allocator given to init (non-NULL once initialized)
    void *buf1;              // 0x1ca0: 0xf00-byte buffer
    void *buf2;              // 0x1ca4: 0x400-byte buffer
    u8 unk_1ca8[0x1cc4 - 0x1ca8];
    s32 state;               // 0x1cc4: the state machine index (0 to 15)
    u8 unk_1cc8[0x1cd8 - 0x1cc8];
    s32 timer;               // 0x1cd8
    u8 unk_1cdc;             // 0x1cdc: flag returned by func_02090ecc
    u8 unk_1cdd;             // 0x1cdd
} WirelessManagerWork;

#endif
