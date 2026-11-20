#ifndef KNIFE_COMM_SINGLEPLAY_WARP_API_H
#define KNIFE_COMM_SINGLEPLAY_WARP_API_H

// Functions defined in src/engine/singleplay_warp*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL Knife_Single_SinglePlay_WarpAtariCheck(void *self, Entity *e);
}

#endif
