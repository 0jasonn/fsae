#ifndef SDK_OS_OS_RESET_H
#define SDK_OS_OS_RESET_H

// TwlSDK OS reset: receives the ARM7's reset command over PXI.
#include "types.h"

extern u16 data_02129c90; // set once OS_InitReset has run

extern "C" {
void OS_InitReset(void);
}

#endif
