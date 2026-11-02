#ifndef WIP_B_IROYUKA_2_H
#define WIP_B_IROYUKA_2_H

#include "engine/functions.h"

// Not in engine/functions.h yet: copies a block to VRAM during VBlank (original SetDataVBlank(void const*, void*, unsigned long), 0x02029d88)
void SetDataVBlank(const void *src, void *dst, u32 size);
// Original UpdateIroyuka() (0x0204d3ac), mangled _Z13UpdateIroyukav
void UpdateIroyuka(void);

#endif
