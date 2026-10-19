#ifndef UNKNOWN_WIP_F_IDOYUKASP_H
#define UNKNOWN_WIP_F_IDOYUKASP_H

#include "engine/functions.h"
#include "object/setcommon.h"

// idoyukaSp actor tables (renamed in scratch/agentF/renames.txt).
extern const EntityFunc idoyukaSp_actions[]; // idoyukaSp_actions, indexed by e->action
extern u16 idoyukaSp_list[];           // idoyukaSp_list, 8-byte entries (4 u16), indexed by e->timer

// Entity overlay: u32 at 0x60 holds the flags this actor waits for (set in idoyukaSp_init from ParseTypeBits).
typedef struct Vars_IdoyukaSp {
    /* 00 */ u8 unk_00[0x60];
    /* 60 */ u32 typeBits;
} Vars_IdoyukaSp;
#define VIDOYUKA(e) VARS(Vars_IdoyukaSp, e)


#endif
