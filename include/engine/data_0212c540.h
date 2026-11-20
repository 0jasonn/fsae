#ifndef ENGINE_DATA_0212C540_H
#define ENGINE_DATA_0212C540_H

#include "types.h"

// Two halfwords at 0x0212c540 (next symbol data_0212c544).
typedef struct UnkStruct_0212c540 {
    /* 00 */ u16 flags;   // bit 0 set by the multiplay warp (multiplay_4), bit 2 by the encounter timer (encnt_3)
    /* 02 */ u16 unk_2;   // the enemy code tests > 1 (em00, em05, em0b, em0c, em1a, em1e, em2b) and == 1 (EmDie)
} UnkStruct_0212c540;
extern UnkStruct_0212c540 data_0212c540;

#endif
