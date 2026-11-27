#ifndef WIP_NWM_INIT_H
#define WIP_NWM_INIT_H

#include "types.h"

extern u8 data_021277d4;                // non-zero once the NWM layer is initialised

extern "C" {
u32 NWMi_CheckInitialized(void);
}

#endif
