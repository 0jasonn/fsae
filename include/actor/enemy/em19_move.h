#ifndef ACTOR_ENEMY_EM19_MOVE_H
#define ACTOR_ENEMY_EM19_MOVE_H

#include "engine/functions.h"

void setActionAnim3(Entity *e); // original setActionAnim3(OBJ_WORK_*), 0x0203e784

// Grid walking action of em19 (original em19_move(OBJ_WORK_*)), 0x0203e324.
void em19_move(Entity *e);

#endif
