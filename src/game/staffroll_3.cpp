#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/subtask.h"

// Functions in this file (provisional name for a func_ address):
//   subTask_staffroll_releaseEntry subTask_staffroll_releaseEntry (0x020adfe4): tail call to subTask_staffroll_release (0x020adf84)

extern "C" void subTask_staffroll_release(void);

// subTask_staffroll_releaseEntry (0x020adfe4): entry of the release step, jumps to subTask_staffroll_release
ARM void subTask_staffroll_releaseEntry(void) {
    subTask_staffroll_release();
}
