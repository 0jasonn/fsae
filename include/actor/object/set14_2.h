#ifndef WIP_C_SET14_2_H
#define WIP_C_SET14_2_H

#include "engine/functions.h"

// Set14 rotation helpers (file-local to src/wip/C/set14_2.cpp)
extern "C" u8 plkaiten(Entity *e, Entity *other); // original plkaiten(OBJ_WORK_*, OBJ_WORK_*), 0x02064a20
extern const u32 flagBits[];                      // flag per entity type (flagBits, 0x020cf9b8)
extern const s8 data_020da10c[];                  // (dx, dy) pairs of the rotation path, indexed by turn state (data_020da10c)

#endif
