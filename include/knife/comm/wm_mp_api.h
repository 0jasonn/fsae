#ifndef KNIFE_COMM_WM_MP_API_H
#define KNIFE_COMM_WM_MP_API_H

// Functions defined in src/engine/wm_mp*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL Knife_Comm_WirelessManager_allocMPBuffer(void *self);
}

#endif
