#include "engine/functions.h"
#include "global.h"

extern "C" {
void *func_020c2264(u32 start, u32 end, s32 tag);
void *func_020c2440(u32 *heap, u32 size, s32 flag);
void *func_020c24f4(u32 *heap, u32 size, s32 flag);
void SndRangeTree_DecodeBounds(u32 *out, u8 *src);
void SndRangeTree_UnlinkChild(void *list, u8 *node);
void func_020c25a4(void *list, u32 *bounds);
void *func_020c2120(void *obj, u32 tag, void *list, u32 a, u32 b);
}

// Creates a heap over the region [base, base + size) with both ends aligned to 4 bytes. Returns 0 when the region is
// empty or too small for a heap (0x4c bytes at least).
extern "C" void *SndHeap_Create(u32 base, u32 size, s32 tag);
ARM void *SndHeap_Create(u32 base, u32 size, s32 tag) {
    u32 start;
    u32 end;

    end = size + base;
    start = base + 3;
    end &= ~3;
    start &= ~3;
    if (start > end || end - start < 0x4c) {
        return 0;
    }
    return func_020c2264(start, end, tag);
}

// Allocates from the heap: a zero flag takes the block from the low end, a negative flag from the high end (its
// magnitude is passed on). Sizes are rounded up to 4 bytes; a zero size becomes 1 byte.
extern "C" void *SndHeap_Allocate(u32 *heap, u32 size, s32 flag);
ARM void *SndHeap_Allocate(u32 *heap, u32 size, s32 flag) {
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3;
    if (flag >= 0) {
        return func_020c2440(heap, size, flag);
    }
    return func_020c24f4(heap, size, -flag);
}

// Frees a block given its user pointer: the block header is 0x10 bytes before it. The block's bounds are decoded
// and the block goes back to the free list at +0x2c, then merged into the list at +0x24.
extern "C" void SndHeap_Free(u32 *heap, u8 *block);
ARM void SndHeap_Free(u32 *heap, u8 *block) {
    u8 *node;
    u32 bounds[2];

    node = block - 0x10;
    SndRangeTree_DecodeBounds(bounds, node);
    SndRangeTree_UnlinkChild((u8 *)heap + 0x2c, node);
    func_020c25a4((u8 *)heap + 0x24, bounds);
}

// Initialises a region through func_020c2120 (tag 'HMRF'), then copies the bounds at +0x18 and +0x1c into the words at
// +0x24 and +0x28 and clears the word at +0x2c. Returns the heap.
extern "C" void *SndHeap_InitRegion(u32 *heap, u32 a, u32 b);
ARM void *SndHeap_InitRegion(u32 *heap, u32 a, u32 b) {
    func_020c2120(heap, 0x46524d48, (u8 *)heap + 0x30, a, b);
    heap[9] = heap[6];
    heap[10] = heap[7];
    heap[11] = 0;
    return heap;
}

// Takes size bytes from the low end of the heap at alignment align. Returns the block start, or 0 when it does not fit.
// When the flag word before the heap has bit 0 set, the taken bytes are cleared with zeros.
extern "C" void *SndHeap_AllocLow(u32 *heap, u32 size, u32 align);
ARM void *SndHeap_AllocLow(u32 *heap, u32 size, u32 align) {
    u32 start;
    u32 next;
    u32 cleared;
    u8 flags;

    start = ((align - 1) + heap[0]) & ~(align - 1);
    next = size + start;
    if (next > heap[1]) {
        return 0;
    }
    cleared = next - heap[0];
    flags = heap[-1] & 0xff;
    if (flags & 1) {
        OSi_CpuClear32(0, (void *)heap[0], cleared);
    }
    heap[0] = next;
    return (void *)start;
}

// Takes size bytes from the high end of the heap at alignment align. Returns the block start, or 0 when it would
// overlap the low end. Clears the taken bytes the same way as SndHeap_AllocLow.
extern "C" void *SndHeap_AllocHigh(u32 *heap, u32 size, u32 align);
ARM void *SndHeap_AllocHigh(u32 *heap, u32 size, u32 align) {
    u32 start;
    u32 cleared;
    u8 flags;

    start = (heap[1] - size) & ~(align - 1);
    if (start < heap[0]) {
        return 0;
    }
    cleared = heap[1] - start;
    flags = heap[-1] & 0xff;
    if (flags & 1) {
        OSi_CpuClear32(0, (void *)start, cleared);
    }
    heap[1] = start;
    return (void *)start;
}
