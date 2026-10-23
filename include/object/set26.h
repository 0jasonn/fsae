#ifndef WIP_G_SET26_H
#define WIP_G_SET26_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Actor fields of the item units (file-local overlay, offsets from the original code).
typedef struct Vars_Set26 {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits; // ParseTypeBits(type), tested against em12_typeMasks[area] in itemget_type1_move
} Vars_Set26;

extern const EntityFunc set26_typeTable[];        // indexed by e->type2, was set26_typeTable
extern const EntityFunc set26_type0Table[];       // indexed by e->action, was set26_type0Table
extern const EntityFunc set26_type1Table[];       // indexed by e->action, was set26_type1Table
extern const u8 itemget_type0_hitbox[];           // hitbox of the item, was itemget_type0_hitbox
extern const u32 flagBits[];                      // area mask bit per type

#endif
