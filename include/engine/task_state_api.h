#ifndef ENGINE_TASK_STATE_API_H
#define ENGINE_TASK_STATE_API_H

// Functions defined in src/engine/task_state*.cpp.

#include "engine/entity.h"

extern "C" {
void Task_Flush(s32 flag);
void Task_Start(void);
}

#endif
