#ifndef SDK_MI_MI_CACHE_H
#define SDK_MI_MI_CACHE_H

// TwlSDK MI block cache: blocks of (1 << shift) bytes kept in lists linked through the first word.
#include "types.h"

typedef struct MiCacheBlock {
    /* 00 */ struct MiCacheBlock *next;
    /* 04 */ u32 index;      // block number
    /* 08 */ u8 *buffer;
} MiCacheBlock;

typedef struct MiCache {
    /* 00 */ u32 shift;
    /* 04 */ MiCacheBlock *used;      // blocks holding data
    /* 08 */ MiCacheBlock *free;
    /* 0c */ MiCacheBlock *pending;   // blocks waiting to be loaded
    /* 10 */ u32 pendingCount;
    /* 14 */ u32 freeCount;
    /* 18 */ u32 usedCount;
} MiCache;

// Reader passed to MI_LoadCache: read(argument, buffer, offset, size) fills one block.
typedef struct MiCacheReader {
    /* 00 */ u32 argument;
    /* 04 */ void (*read)(u32 argument, u8 *buffer, u32 offset, u32 size);
} MiCacheReader;

extern "C" {
void MI_LoadCache(MiCache *cache, MiCacheReader *reader);
}

#endif
