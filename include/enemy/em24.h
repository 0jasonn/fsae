#ifndef UNKNOWN_B_ACTOR_0204001C_H
#define UNKNOWN_B_ACTOR_0204001C_H

#include "engine/entity.h"

typedef struct Vars_0204001c {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *unk_64; // child object, allocated by func_02084f98 (0x58 bytes)
    /* 68 */ u8 unk_68[0x14];
    /* 7c */ u16 unk_7c;
    /* 7e */ u16 unk_7e;
} Vars_0204001c;
#define V(e) VARS(Vars_0204001c, e)

extern const void *data_020d310c[];
extern const s8 data_020d2e64[];
extern const s8 data_020d2e3c[];
extern const EntityFunc data_020d2fb4[];
extern const EntityFunc data_020d2fe4[];



#endif
