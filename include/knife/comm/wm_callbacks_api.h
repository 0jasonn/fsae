#ifndef ENGINE_WM_CALLBACKS_API_H
#define ENGINE_WM_CALLBACKS_API_H

// Functions defined in src/engine/wm_callbacks*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_Enable(void *result);
void Knife_Comm_WirelessManager_callback_WM_ResetStep(void *result);
}

#endif
