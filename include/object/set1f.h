#ifndef UNKNOWN_WIP_F_SET1F_H
#define UNKNOWN_WIP_F_SET1F_H

#include "engine/functions.h"
#include "object/setcommon.h"

// Set1f actor tables (renamed in scratch/agentF/renames.txt).
extern const EntityFunc set1f_actions[];  // set1f_actions, indexed by e->action
extern const u8 set1f_typeOffset[];       // set1f_typeOffset, added to e->unk_20 by type
extern const s8 set1f_zTable[];           // set1f_zTable, 8 entries, z offsets cycled by timer

extern u16 data_0212c594; // frame counter

// Unnamed callee (original address 0x02025d8c, size 0x10), returns a 4-bit value for spriteSettings.
extern "C" u32 func_02025d8c(u8 type);

#endif
