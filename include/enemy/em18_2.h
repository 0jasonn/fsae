#ifndef WIP_B_EM18_2_H
#define WIP_B_EM18_2_H

#include "engine/functions.h"

// em18 dispatch tables in ROM (index = e->action).
extern const EntityFunc em18_actionTable[]; // em18_actionTable
extern const EntityFunc em18_type0Table[];  // em18_type0Table

#include "enemy/delprt.h"
extern "C" void func_02084a20(Entity *e);   // thumb helper, dsd name

#endif
