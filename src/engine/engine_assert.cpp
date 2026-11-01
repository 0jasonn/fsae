#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/task_state_api.h"

extern "C" void Engine_AssertFail(u32 a, u32 b, u32 c, u32 d);
extern const char data_020df6c0[];

// Prints the message at data_020df6c0 with the four values through func_02007f58, then calls Task_Start.
void Engine_AssertFail(u32 a, u32 b, u32 c, u32 d) {
    func_02007f58(data_020df6c0, a, b, c, d);
    Task_Start();
}
