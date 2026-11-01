#ifndef WIP_C_OBJPRIO_H
#define WIP_C_OBJPRIO_H

// Declarations for src/wip/C/objprio.cpp. The map cell lookup is thumb code without an original name.
#include "engine/entity.h"

int func_02083c8c(int x, int y, u16 layer); // thumb, map cell at (x, y) on the layer (C++, as in functions.h)

// Returns 1 when the lift priority is set, 0 otherwise (declared as void in engine/functions.h; the reviewer
// should change that prototype to int).
int ObjLiftPrioCheck(Entity *e);

#endif
