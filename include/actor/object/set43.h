#ifndef WIP_A_SET43_H
#define WIP_A_SET43_H

#include "engine/functions.h"

// Actor fields of the Set43 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set43 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ u16 waitCounter;   // counts down in set43_kasoku before the timer is used
    /* 66 */ u16 savedCounter;  // copied into waitCounter by set43_gensoku when the sequence ends
    /* 68 */ u8 flag;           // non-zero: set43_wait clears linkedEntity
    /* 69 */ u8 unk_69[7];
    /* 70 */ u16 limit;         // compared with subtimer in set43_kasoku
} Vars_Set43;

extern const EntityFunc set43Table[]; // set43Table, indexed by action
extern u16 frameCounter;       // frame counter
extern u32 em12_typeMasks[];
int switchcheck(Entity *e);
void setwind(Entity *e);
void plmove(Entity *e);

#endif
