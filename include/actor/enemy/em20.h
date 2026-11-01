#ifndef WIP_B_EM20_H
#define WIP_B_EM20_H

#include "engine/functions.h"

extern const EntityFunc em20_stateTable[];  // em20_stateTable, used by EnemyFunctionHandler (type 0)
extern const EntityFunc em20_actionTable[]; // em20_actionTable, index = e->action
extern const EntityFunc kamen_actionTable[]; // kamen_actionTable, index = e->action (type != 0)

int magneCheck(Entity *e);     // original magneCheck(OBJ_WORK_*), nonzero when the magnet check holds
int dushInitCheck(Entity *e);  // original dushInitCheck(OBJ_WORK_*), nonzero when a dash can start

#endif
