#include "engine/functions.h"
#include "global.h"

// Linear heap cursors (provisional): the words of a heap are indexed as u32. heap[6] is the region start (+18), heap[7]
// the region end (+1c), heap[8] the flag word (+20), heap[9] the low cursor (+24), heap[10] the high cursor or pool block
// size (+28), heap[11] the first node of the high chain (+2c).
extern "C" void *SndHeap_InitRegion(u32 *heap, u32 a, u32 b);
extern "C" void *SndHeap_AllocLow(u32 *heap, u32 size, u32 align);
extern "C" void *SndHeap_AllocHigh(u32 *heap, u32 size, u32 align);

// SndHeap_Rewind: moves the low cursor back to the region start and clears the first word of the high chain.
extern "C" void SndHeap_Rewind(u32 *heap);
ARM void SndHeap_Rewind(u32 *heap) {
    heap[9] = heap[6];
    heap[11] = 0;
}

// SndHeap_ResetHigh: points the prev word of every node in the high chain at the region end, then sets the high cursor to
// the region end.
extern "C" void SndHeap_ResetHigh(u32 *heap);
ARM void SndHeap_ResetHigh(u32 *heap) {
    u32 *node;

    node = (u32 *)heap[11];
    if (node != 0) {
        do {
            node[2] = heap[7];
            node = (u32 *)node[3];
        } while (node != 0);
    }
    heap[10] = heap[7];
}

// SndHeap_InitLinear: aligns the region [base, base + size) to 4 bytes at both ends and initialises it through
// SndHeap_InitRegion. Returns 0 when the region is empty or smaller than 0x30 bytes.
extern "C" void *SndHeap_InitLinear(u32 base, u32 size, u32 b);
ARM void *SndHeap_InitLinear(u32 base, u32 size, u32 b) {
    u32 start;
    u32 end;

    end = size + base;
    start = base + 3;
    end &= ~3;
    start &= ~3;
    if (start > end || end - start < 0x30) {
        return 0;
    }
    return SndHeap_InitRegion((u32 *)start, end, b);
}

