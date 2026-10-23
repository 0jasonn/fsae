#ifndef WIP_C_TAMA07_H
#define WIP_C_TAMA07_H

// Declarations for the Tama07 actor family (src/wip/C/tama07.cpp).
#include "engine/functions.h"
#include "global.h"
#include "engine/player.h"

extern "C" {
int func_02085294(void); // label, thumb: state index of the Tama07 dispatcher
}

extern const EntityFunc data_020dced4[]; // Tama07 normal action table, indexed by e->action
extern const EntityFunc data_020dcf28[]; // Tama07 dispatcher table, indexed by func_02085294()
extern const s16 data_020dcf18[]; // (x, y) offsets for tama07_init, indexed by 2 * (direction >> 3)
extern const u8 data_020dcec2[]; // hitbox of the Tama07 family

// The parent of a Tama07 actor: the word at 0x64 holds the actor it carries.
typedef struct Vars_Tama07Parent {
    /* 00 */ u8 unk_00[0x64];
    /* 64 */ Entity *carried;
} Vars_Tama07Parent;

void tama07_remove(Entity *e); // original name unknown (tama07_remove)

#endif
