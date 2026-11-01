#ifndef WIP_B_EM22_H
#define WIP_B_EM22_H

#include "engine/functions.h"

extern const EntityFunc em22_actionTable[]; // em22_actionTable, index = e->action

void dmgmgr(Entity *e); // original dmgmgr(OBJ_WORK_*), damage manager of the actor

#endif
