#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/engine_romhalf.h"

// Returns the halfword at data_020dfb7c in the ROM data.
extern u16 data_020dfb7c;


u16 Engine_ReadRomHalf(void) {
    return data_020dfb7c;
}
