#ifndef WIP_B_EM20_7_H
#define WIP_B_EM20_7_H

#include "engine/functions.h"
#include "enemy/kamen.h"

extern const s8 em20_dushOffsetTable[]; // em20_dushOffsetTable, 4 signed offsets per animation frame: x, y, x, y (dust positions)
int dushCheck(Entity *e);               // original dushCheck(OBJ_WORK_*), returns nonzero when the dash ends

#endif
