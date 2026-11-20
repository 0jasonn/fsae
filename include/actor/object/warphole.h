#ifndef WIP_F_WARPHOLE_H
#define WIP_F_WARPHOLE_H

// Prototypes used by src/wip/F/warphole*.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

void pos_copy(Entity *src, Entity *dst); // 0x0205e05c, original name pos_copy(OBJ_WORK_*, OBJ_WORK_*)
// 0x0205e114, original warphole_exit(OBJ_WORK_*), defined in src/object/warphole_3.cpp
void warphole_exit(Entity *e);

#endif
