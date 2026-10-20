#ifndef WIP_G_SET13_H
#define WIP_G_SET13_H

#include "engine/functions.h"
#include "engine/player.h"
#include "object/setcommon.h"

// Set13 actor fields and tables, shared by the set13 units.
typedef struct Vars_Set13 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;    // ParseTypeBits(type), tested against em12_typeMasks[areaIndex]
    /* 64 */ u8 unk_64[0xc];
    /* 70 */ u16 cellValue70; // saved by hidari_writecell
    /* 72 */ u8 unk_72[2];
    /* 74 */ u16 cellValue74; // saved by hidari_writecell
    /* 76 */ u16 typeMask76;  // typeBits & em12_typeMasks[areaIndex], stored by set13_move0
    /* 78 */ s8 step;         // +1 or -1, direction of the move
    /* 79 */ u8 unk_79[3];
    /* 7c */ u16 *cellPtr;    // this actor's cell in the background map
} Vars_Set13;

extern const EntityFunc set13_stateTable[]; // indexed by e->action (was set13_stateTable)
extern u32 em12_typeMasks[];
#endif
