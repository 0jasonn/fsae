#ifndef ACTOR_ENEMY_EM12_WAIT2_H
#define ACTOR_ENEMY_EM12_WAIT2_H

#include "engine/functions.h"

extern u8 data_0212ced8[]; // PlayerData.entity pointers, stride 0x94 (playerWork[i].entity)
extern u16 frameCounter;   // frame counter (halfword)

// Second wait state of em12 (original em12_wait2(OBJ_WORK_*)), 0x0203b594.
void em12_wait2(Entity *e);

#endif
