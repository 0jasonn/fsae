#ifndef WIP_C_SET25_3_H
#define WIP_C_SET25_3_H

#include "engine/functions.h"

// Callees and tables of the kudake and smoke functions that engine/functions.h and object/set25.h do not declare.
extern "C" void kudakeSet(Entity *e);     // original kudakeSet(OBJ_WORK_*), 0x0206677c (parked in scratch/agentC/nonmatching)
extern "C" void recell0(Entity *e);         // original name recell0, 0x02066910 (not yet decompiled)
extern const s8 data_020da41c[];            // per-type offset of the kudake spawn position (data_020da41c)
extern const u8 data_020da4ec[];            // damage per contact byte, indexed by the other entity's unk_40 (data_020da4ec)
extern const u8 data_020da420[];            // x/y offset of the smoke pieces, indexed by timer >> 1 (data_020da420)

#endif
