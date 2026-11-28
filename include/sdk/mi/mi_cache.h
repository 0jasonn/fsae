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
    /* 10 */ u32 usedCount;          // blocks on the used list
    /* 14 */ u32 freeCount;          // blocks on the free list
    /* 18 */ s32 pendingBalance;     // -(blocks queued and not loaded yet): -1 per block taken from the free list, +1 per load
} MiCache;

// Reader passed to MI_LoadCache: read(argument, buffer, offset, size) fills one block.
typedef struct MiCacheReader {
    /* 00 */ u32 argument;
    /* 04 */ void (*read)(u32 argument, u8 *buffer, u32 offset, u32 size);
} MiCacheReader;

// Set to 1 when a request left blocks unqueued because the free list was empty (cleared elsewhere).
extern u32 data_02129880;

extern "C" {
void MI_InitCache(MiCache *cache, u32 blockSize, u8 *buffer, u32 bufferSize);
void func_02016788(MiCache *cache, u32 firstBlock, u32 mask); // queues blocks firstBlock + bit for every bit of mask
void MI_LoadCache(MiCache *cache, MiCacheReader *reader);
}

#endif
