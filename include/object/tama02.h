#ifndef WIP_C_TAMA02_H
#define WIP_C_TAMA02_H

// Declarations for the tama02 actor family (src/wip/C/tama02*.cpp).
#include "engine/functions.h"
#include "engine/player.h"
#include "global.h"

extern "C" {
void func_0208b644(Entity *e); // label, thumb, no C++ name
}

extern const EntityFunc data_020dcb98[]; // tama02 dispatcher action table, indexed by e->action
extern const s8 data_020dcb94[]; // signed byte table, indexed by the parent's kind (parent+0x7c)
extern const u8 data_02117ba0[];

// Actor-specific fields of a tama02 actor (its own Entity) and of its parent.
typedef struct Vars_Tama02 {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *partner; // the linked actor (Entity pointer stored at 0x64)
    /* 68 */ u8 unk_68[0xa];
    /* 72 */ u16 swingTimer; // counts down while the actor swings
    /* 74 */ u16 resetTimer; // reset to 0x18..0x27 when it runs out
} Vars_Tama02;

// The partner actor: a word at 0x04 links it to an owner (nonzero while linked).
typedef struct Vars_Tama02Partner {
    /* 00 */ u8 unk_00[4];
    /* 04 */ s32 linkValue;
} Vars_Tama02Partner;

typedef struct Vars_Tama02Parent {
    /* 00 */ u8 unk_00[0x7c];
    /* 7c */ u8 parentKind; // index into data_020dcb94
} Vars_Tama02Parent;

#endif
