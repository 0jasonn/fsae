#ifndef UNKNOWN_WIP_F_CRYSTAL_H
#define UNKNOWN_WIP_F_CRYSTAL_H

#include "object/setcommon.h"

// Crystal actor fields (file-local overlay for src/object/crystal.cpp, not shared).
typedef struct Vars_Crystal {
    /* 00 */ u8 unk_00[0x1c];
    /* 1c */ u32 spriteWord;    // Entity.spriteSettings as one word: bit 0, bits 14-15, bits 16-19, bit 10-11, bits 30-31
    /* 20 */ u8 unk_20[0x40];
    /* 60 */ u16 anchorY;       // template y + 0x38, read back by the crystal's move code
} Vars_Crystal;
#define VCRY(e) VARS(Vars_Crystal, e)

// Byte at PlayerData.unk_3d[0x4e] (0x8b of the player work), read as bitfields
typedef struct PlFlagsByte { u8 b0 : 2; u8 b2 : 2; u8 b4 : 4; } PlFlagsByte;

extern const EntityFunc crystal0_actions[]; // crystal0_actions, indexed by e->action
extern const EntityFunc crystal1_actions[]; // crystal1_actions, indexed by e->action
extern const EntityFunc cry1_plate_actions[]; // cry1_plate_actions, indexed by e->action

#endif
