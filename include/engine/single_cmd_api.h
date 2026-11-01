#ifndef ENGINE_SINGLE_CMD_API_H
#define ENGINE_SINGLE_CMD_API_H

// Functions defined in src/engine/single_cmd*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Single_SinglePlay_SetObjMoveReqNo(void *self, void *obj, u8 player, s32 delta, u8 dir);
}

#endif
