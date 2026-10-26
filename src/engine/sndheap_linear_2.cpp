#include "engine/functions.h"
#include "global.h"

extern "C" void *SndHeap_AllocLow(u32 *heap, u32 size, u32 align);
extern "C" void *SndHeap_AllocHigh(u32 *heap, u32 size, u32 align);
extern "C" void SndHeap_Rewind(u32 *heap);
extern "C" void SndHeap_ResetHigh(u32 *heap);

// SndHeap_ReserveLinear: reserves size bytes from the linear heap (a zero size becomes 1 byte, the size is rounded up to 4).
// A flag of zero or more takes the block from the low cursor with that alignment, a negative flag from the high cursor.
extern "C" void *SndHeap_ReserveLinear(u32 *heap, u32 size, s32 flag);
ARM void *SndHeap_ReserveLinear(u32 *heap, u32 size, s32 flag) {
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3;
    if (flag >= 0) {
        return SndHeap_AllocLow(heap + 9, size, flag);
    }
    return SndHeap_AllocHigh(heap + 9, size, -flag);
}

// SndHeap_ResetFlags: bit 0 of flags rewinds the low cursor, bit 1 resets the high cursor.
extern "C" void SndHeap_ResetFlags(u32 *heap, u32 flags);
ARM void SndHeap_ResetFlags(u32 *heap, u32 flags) {
    if (flags & 1) {
        SndHeap_Rewind(heap);
    }
    if (flags & 2) {
        SndHeap_ResetHigh(heap);
    }
}

// SndHeapPool_Pop: takes the first block of a free list whose next word is at +0; returns the block or 0.
extern "C" void *SndHeapPool_Pop(void **head);
ARM void *SndHeapPool_Pop(void **head) {
    void *block;

    block = *head;
    if (block != 0) {
        *head = *(void **)block;
    }
    return block;
}

// SndHeapPool_Alloc: pops a block from the pool at heap+0x24. When the flag word has bit 0 set the block is cleared with
// zeros over the pool block size (heap+0x28).
extern "C" void *SndHeapPool_Alloc(u32 *heap);
ARM void *SndHeapPool_Alloc(u32 *heap) {
    void *block;
    u32 blockSize;

    block = SndHeapPool_Pop((void **)(heap + 9));
    if (block != 0) {
        blockSize = heap[10];
        if ((u8)heap[8] & 1) {
            OSi_CpuClear32(0, block, blockSize);
        }
    }
    return block;
}

// SndHeapPool_Push: links block at the front of the pool at heap+0x24.
extern "C" void SndHeapPool_Push(u32 *heap, void *block);
ARM void SndHeapPool_Push(u32 *heap, void *block) {
    *(void **)block = (void *)heap[9];
    heap[9] = (u32)block;
}
