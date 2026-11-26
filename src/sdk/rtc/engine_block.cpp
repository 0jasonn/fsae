#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/rtc/rtc.h"

// Engine_GetBlockD54() (0x0201a468): returns the RTC work proper, which starts at the lock word (+4) of the library state
// (dsd: data_02129d54).
s32 *Engine_GetBlockD54(void) {
    return &data_02129d50.busy;
}
