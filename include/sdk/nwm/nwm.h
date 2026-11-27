#ifndef SDK_NWM_NWM_H
#define SDK_NWM_NWM_H

// TwlSDK NWM library (DSi wireless).
#include "types.h"

extern u8 data_021277d4; // non-zero once the NWM layer is initialised

extern "C" {
u32 NWMi_CheckInitialized(void);
}

#endif
