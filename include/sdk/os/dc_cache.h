#ifndef SDK_OS_DC_CACHE_H
#define SDK_OS_DC_CACHE_H

#include "types.h"

extern "C" {
void DC_FlushAll(void);
void DC_InvalidateRange(void *start, u32 size);
void DC_StoreRange(void *start, u32 size);
void DC_FlushRange(const void *start, u32 size);
void DC_WaitWriteBufferEmpty(void);
void IC_InvalidateAll(void);
void IC_InvalidateRange(void *start, u32 size);
void OSi_WaitVCount0(void);
}

#endif
