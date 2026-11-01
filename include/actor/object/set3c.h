#ifndef WIP_F_SET3C_H
#define WIP_F_SET3C_H

// Prototypes used by src/wip/F/set3c.cpp that engine/functions.h does not declare yet (to be moved there).
#include "engine/functions.h"

int func_02085ccc(Entity *e);  // 0x02085ccc, nonzero when the set3c actor's cell is held (cellcalls.h)
void SKemuriSet(Entity *e);    // 0x02076904, original name SKemuriSet(OBJ_WORK_*)
int anacheck(Entity *e);       // 0x0205ccf8, original name anacheck(OBJ_WORK_*)

#endif
