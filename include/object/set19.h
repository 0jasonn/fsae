#ifndef WIP_G_SET19_H
#define WIP_G_SET19_H

#include "engine/functions.h"

// Actor fields of the Set19 family (file-local overlay, offsets from the original code).
typedef struct Vars_Set19 {
    /* 00 */ u8 unk_00[0x78];
    /* 78 */ u16 cellValue;   // BG cell value under the entity, taken in set19_init
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 *cellPtr;    // BG cell under the entity, set in set19_init
} Vars_Set19;

extern const EntityFunc set19_stateTable[]; // indexed by e->action, was set19_stateTable
extern u16 data_0213492c[];                 // (x, y) u16 pairs per area, see enemy/em12.h
extern u16 em12_spawnOffsetY[];
extern u32 em12_typeMasks[];
extern const u32 flagBits[];
void MultiEventSet(u16 *list, u8 a, u8 b, u8 c); // original MultiEventSet(unsigned short*, unsigned char, unsigned char, unsigned char)

#endif
