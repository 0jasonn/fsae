#ifndef UI_OPDEMO_H
#define UI_OPDEMO_H

// Opening-demo helpers used by the C units that the shared header does not declare yet.
#include "engine/functions.h"

void PutNPC(u8 index);                  // original PutNPC(unsigned char), frees an NPC slot from data_02134d30

extern u16 data_0212c510;               // flag word also declared in game/multiplay.h

// Engine and player helpers that are not in engine/functions.h yet (see report).
void RotateObjWork(u8 list);            // original RotateObjWork(unsigned char), 0x0204c1ec
extern u8 data_0212c4e8;                // byte cleared at the start of AfterPlayer
int func_02083d18(Entity *e, int dx, int dy); // C++ linkage (_Z13func_02083d18P9OBJ_WORK_ii), same as enemycommon.h
#include "engine/frame_counter.h"
#include "engine/palette_buff.h"

#endif
