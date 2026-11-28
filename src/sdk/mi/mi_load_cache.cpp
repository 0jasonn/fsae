#include "sdk/mi/mi_cache.h"
#include "sdk/os/os_interrupts.h"

// Loads every pending block of the cache through the reader callback.
void MI_LoadCache(MiCache *cache, MiCacheReader *reader) {
    u32 one = 1;
    MiCacheBlock *block;

    for (;;) {
        block = cache->pending;
        if (block == 0) {
            return;
        }
        reader->read(reader->argument, block->buffer, block->index << cache->shift, one << cache->shift);
        u32 irq = OS_DisableInterrupts();
        cache->pending = block->next;
        block->next = cache->used;
        cache->used = block;
        cache->usedCount++;
        cache->pendingBalance++;
        OS_RestoreInterrupts(irq);
    }
}
