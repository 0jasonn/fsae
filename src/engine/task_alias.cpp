#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void Task_Start(void);
extern "C" void Task_StartAlias(void);

// Tail call to Task_Start (the original jumps to it).
ARM void Task_StartAlias(void) {
    Task_Start();
}
