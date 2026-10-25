#ifndef WIP_C_SET21_2_H
#define WIP_C_SET21_2_H

#include "engine/functions.h"

// Callees and tables of the set21 init that engine/functions.h does not declare yet.
u32 Cockpit_GetTableByte(s32 type);           // original _Z20Cockpit_GetTableBytel (C++ linkage, long argument), 0x02025d8c
extern "C" void func_02085fac(Entity *e);     // thumb, no original name
extern const u8 data_02115ad8[];              // hitbox table of the set21 actor (data_02115ad8)
extern "C" void set21_move(Entity *e);                // original set21_move(OBJ_WORK_*), 0x02065c40 (C++ linkage, not yet in functions.h)

#endif
