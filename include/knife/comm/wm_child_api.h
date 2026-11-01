#ifndef ENGINE_WM_CHILD_API_H
#define ENGINE_WM_CHILD_API_H

// Functions defined in src/engine/wm_child*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_ChildEntry(void *result);
void Knife_Comm_WirelessManager_callback_WM_StepTimer3(void *result);
}

#endif
