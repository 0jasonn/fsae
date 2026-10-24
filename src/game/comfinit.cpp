#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "enemy/decls_b.h"

// Functions in this file (provisional name, original function is ComInitState):
//   ComInitState -> ComInitState

extern u8 data_0212c9a8[];   // communication work area, 0x148 bytes
extern u32 data_0212c544;    // communication state word, cleared here
extern u32 opTitleState;    // communication state word, cleared here

// Clears the communication work area and the two state words, finishes the last transfer and starts the
// serial interface.
ARM void ComInitState(void) {
    MIi_CpuClear16(0, data_0212c9a8, 0x148);
    ComFinish(0);
    MultiSioInit();
    data_0212c544 = 0;
    opTitleState = 0;
}
