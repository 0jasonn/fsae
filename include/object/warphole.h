#ifndef WIP_F_WARPHOLE_H
#define WIP_F_WARPHOLE_H

// Prototypes used by src/wip/F/warphole*.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

int func_02084110(void);       // 0x02084110, bit mask of the players in the warp (bits 0..3), original name func_02084110()
void pos_copy(Entity *src, Entity *dst); // 0x0205e05c, original name pos_copy(OBJ_WORK_*, OBJ_WORK_*)

#endif
