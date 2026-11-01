#ifndef WIP_E_PICTOGRAM_INIT_H
#define WIP_E_PICTOGRAM_INIT_H

// Static initializer of the global PictogramRenderer block at data_0217d650 (0x020a4888), called from the
// __sinit table at 0x020df438. Its vtable is data_0212499c, the TextRenderer-side table (see pictogram.h).

#include "engine/functions.h"

extern "C" {
void *Knife_Message_PictogramRenderer_initGlobal(void *self);
void MI_CpuFill8(void *dst, u8 value, u32 size);
}

#endif
