#ifndef ENGINE_WM_MEASURE_API_H
#define ENGINE_WM_MEASURE_API_H

// Functions defined in src/engine/wm_measure*.cpp.

#include "engine/entity.h"

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_MeasureChannel(void *result);
void Knife_Comm_WirelessManager_callback_WM_StepTimer(void *result);
void Knife_Comm_WirelessManager_callback_WM_StepTimer2(void *result);
}

#endif
