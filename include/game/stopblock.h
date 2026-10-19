#ifndef WIP_C_STOPBLOCK_H
#define WIP_C_STOPBLOCK_H

#include "types.h"

// Stop block record (4 bytes): a key with the cell and layer bits, and a state byte (0xff = active)
typedef struct STOPBLOCK_WORK_ {
    /* 00 */ u16 key;
    /* 02 */ u8 state;
    /* 03 */ u8 unk_03;
} STOPBLOCK_WORK_;

// sbRegistSub (0x0204e7d4, not yet matched): returns non-zero when the block cannot be registered
int sbRegistSub(u16 *key, u8 kind, STOPBLOCK_WORK_ *begin, STOPBLOCK_WORK_ *end);

#endif
