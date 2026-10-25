#ifndef WIP_C_IDO_3_H
#define WIP_C_IDO_3_H

#include "engine/functions.h"

// Callees of the ido wait state that engine/functions.h does not declare yet.
extern "C" int ido_yukaPlMoveCheck(PlayerData *player); // original yukaPlMoveCheck(PL_WORK_*), src/object/ido_2.cpp
extern "C" void Knife_Single_SinglePlay_SetObjMoveReqFlag(u8 *self, Entity *e, u32 mask, s32 a, u8 b); // original (OBJ_WORK_*, unsigned long, long, unsigned char) on SinglePlay

#endif
