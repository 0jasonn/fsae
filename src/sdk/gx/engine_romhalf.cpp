#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/engine_romhalf.h"
#include "sdk/gx/gx.h"

// Returns the display on flag data_020dfb7c (GX_IsDispOn in the SDK).


u16 Engine_ReadRomHalf(void) {
    return data_020dfb7c;
}
