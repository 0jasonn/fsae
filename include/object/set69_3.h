#ifndef WIP_D_SET69_3_H
#define WIP_D_SET69_3_H

// Set69 units after set69_2 (module set69). Shared by src/wip/D/set69_3.cpp and the later set69 units.

#include "engine/functions.h"
#include "engine/player.h"
#include "object/set66.h"

// File-local overlay of the set69 type1 fields (the rupee rush object that is sucked into the pot).
typedef struct Vars_Set69Type1 {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ struct {
        u32 unk_0 : 8;
        u32 b8 : 2; // bits 8-9 of Entity.spriteSettings, a 2 bit field here
        u32 unk_10 : 22;
    } spriteBits;
    /* 20 */ u8 unk_20[0x78 - 0x20];
    /* 78 */ u16 suikomareTimer; // counts down while the object is sucked in
    /* 7a */ u8 unk_7a[2];
    /* 7c */ u16 scaleX;         // ObjAffineSet2 source [0], starts at 0x100
    /* 7e */ u16 scaleY;         // ObjAffineSet2 source [1], starts at 0x100
} Vars_Set69Type1;

extern const EntityFunc set69_type1Actions[]; // set69_type1Actions, indexed by e->action
extern const s8 data_020dc044[];              // two y offsets used by type1_suikomare
extern u32 data_020d70ec[];                   // map load block passed to MapLoad by type0_bgreset
extern u8 data_0212c5ac[];                    // fade block, byte 7 is the blend colour (see misc_d.h)
extern u8 messageRequest[];                   // scene control bytes, see game/message.h
extern s32 em2f_mapFlag;
extern KnifeObjAffineSrcData scrollArgs;     // scale x, scale y, angle for ObjAffineSet2 (scrollArgs, bss)

#endif
