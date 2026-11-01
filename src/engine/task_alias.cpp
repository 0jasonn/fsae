#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/task_alias_api.h"
#include "engine/task_state_api.h"

// Tail call to Task_Start (the original jumps to it).
void Task_StartAlias(void) {
    Task_Start();
}
