#ifndef ENGINE_IRQCOUNT_API_H
#define ENGINE_IRQCOUNT_API_H

// Functions defined in src/engine/irqcount*.cpp.

#include "engine/entity.h"

extern "C" {
u32 IrqCount_Acquire(void);
u32 IrqCount_Release(void);
void Obj_SetWordB4(void *obj, u32 value);
void Os_EnableIrqAndHalt(void);
}

#endif
