#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/os/engine_halfc_api.h"
#include "sdk/os/os_alarm.h"

// Returns the initialised flag of the alarm queue (data_02129c70).

u16 Engine_ReadHalfC(void) {
    return data_02129c70.initialised;
}
