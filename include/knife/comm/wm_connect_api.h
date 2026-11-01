#ifndef ENGINE_WM_CONNECT_API_H
#define ENGINE_WM_CONNECT_API_H

// Functions defined in src/engine/wm_connect*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_ClearFlag(void *result);
void Knife_Comm_WirelessManager_callback_WM_SetEntry(void *result);
void Knife_Comm_WirelessManager_callback_WM_StepTimer5(void *result);
}

#endif
