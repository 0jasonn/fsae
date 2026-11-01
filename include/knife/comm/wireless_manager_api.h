#ifndef ENGINE_WIRELESS_MANAGER_API_H
#define ENGINE_WIRELESS_MANAGER_API_H

// Functions defined in src/engine/wireless_manager*.cpp.

#include "engine/entity.h"

extern "C" {
BOOL Knife_Comm_WirelessManager_init(void *self, void *allocatorPtr, u32 dmaNo);
}

#endif
