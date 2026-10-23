#ifndef WIP_F_SET3D_H
#define WIP_F_SET3D_H

// Prototypes used by src/wip/F/set3d.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

void set3dyure(Entity *e);     // 0x0205d940, original name set3dyure(OBJ_WORK_*)
Entity *settail(Entity *e); // 0x0205d8e4, original name settail(OBJ_WORK_*), returns the child it creates

#endif
