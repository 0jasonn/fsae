#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/engine_halfb_api.h"
#include "sdk/os/os_tick.h"

// Returns the initialised flag of the tick state (data_02129c60).

u16 Engine_ReadHalfB(void) {
    return data_02129c60.initialised;
}
