#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void Mem_SetCore(void *dst, s32 value, u32 size);
extern "C" void *Mem_Set(void *dst, s32 value, u32 size);

// Fills size bytes at dst with value and returns dst.
ARM void *Mem_Set(void *dst, s32 value, u32 size) {
    Mem_SetCore(dst, value, size);
    return dst;
}
