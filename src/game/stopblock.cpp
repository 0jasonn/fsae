#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (original names from the debug build):
//   StopBlockInit

// Two 0xc0 byte work arrays of the stop block system
extern u8 data_02134f30[];
extern u8 data_02134ff0[];

// Clears both stop block work arrays
ARM void StopBlockInit(void) {
    OSi_CpuClear32(0, data_02134f30, 0xc0);
    OSi_CpuClear32(0, data_02134ff0, 0xc0);
}
