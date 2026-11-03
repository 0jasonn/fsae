#ifndef WIP_C_SUBTASK_HBLANK_H
#define WIP_C_SUBTASK_HBLANK_H

#include "types.h"

extern u8 data_02fe0000[]; // start of the shared main-memory area, the flag word is at +0x3ff8

extern "C" {
void subtask_hblank_irq(void); // 0x0209a890
}

#endif
