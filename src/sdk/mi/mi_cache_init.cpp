#include "sdk/mi/mi_cache.h"
#include "engine/clz.h"
#include "sdk/gx/gx_vramcnt.h"
#include "sdk/os/os_interrupts.h"

// Sets up a block cache: blockSize must be a power of two. The bufferSize bytes at buffer hold the block data followed
// by one MiCacheBlock list node per block (12 bytes each); all blocks start on the free list.
void MI_InitCache(MiCache *cache, u32 blockSize, u8 *buffer, u32 bufferSize) {
    u32 count;
    MiCacheBlock *node;

    cache->shift = 32 - CountLeadingZeros(~blockSize & (blockSize - 1));
    cache->usedCount = 0;
    cache->freeCount = 0;
    cache->pendingBalance = 0;
    cache->used = 0;
    cache->free = 0;
    cache->pending = 0;
    count = bufferSize / (blockSize + 12);
    node = (MiCacheBlock *)(buffer + count * blockSize);
    cache->freeCount += count;
    for (; count != 0; count--) {
        node->index = 0;
        node->buffer = buffer;
        buffer += blockSize;
        node->next = cache->free;
        cache->free = node;
        node++;
    }
}

// Queues the blocks firstBlock + n (for every set bit n of mask) for loading. Blocks that are already queued are
// skipped; when the free list is short the least recently used blocks of the used list are released first. Bits of
// blocks that found no free block stay in the flag data_02129880.
void func_02016788(MiCache *cache, u32 firstBlock, u32 mask) {
    s32 diff;
    s32 missing;
    MiCacheBlock **link;
    MiCacheBlock **freeTail;
    u32 left;
    u32 bit;
    u32 irq;
    MiCacheBlock *block;
    MiCacheBlock **tail;

    irq = OS_DisableInterrupts();
    tail = &cache->pending;
    while (*tail != 0) {
        diff = (*tail)->index - firstBlock;
        if ((u32)diff < 0x20 && (mask & (1 << diff))) {
            mask &= ~(1 << diff);
        }
        tail = (MiCacheBlock **)*tail;
    }
    missing = MATH_CountPopulation(mask) - cache->freeCount;
    if (missing > 0) {
        left = cache->usedCount;
        link = &cache->used;
        while (*link != 0) {
            left--;
            if ((s32)left < missing) {
                freeTail = &cache->free;
                while (*freeTail != 0) {
                    freeTail = (MiCacheBlock **)*freeTail;
                }
                *freeTail = *link;
                *link = 0;
                cache->usedCount -= missing;
                cache->freeCount += missing;
                break;
            }
            link = (MiCacheBlock **)*link;
        }
    }
    while (cache->free != 0 && mask != 0) {
        block = cache->free;
        bit = 32 - CountLeadingZeros(~mask & (mask - 1));
        cache->free = block->next;
        block->index = firstBlock + bit;
        block->next = 0;
        *tail = block;
        cache->freeCount--;
        cache->pendingBalance--;
        tail = &block->next;
        mask &= ~(1 << bit);
    }
    OS_RestoreInterrupts(irq);
    if (mask != 0) {
        if (data_02129880 == 0) {
            data_02129880 = 1;
        }
    }
}
