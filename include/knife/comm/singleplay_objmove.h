#ifndef KNIFE_COMM_SINGLEPLAY_OBJMOVE_H
#define KNIFE_COMM_SINGLEPLAY_OBJMOVE_H

#include "engine/entity.h"

extern "C" {
void Knife_Single_SinglePlay_SetObjMoveReqFlag(void *self, Entity *obj, u32 mask, s32 delta, u8 dir);
}

#endif
